#include "VIGeneralBehavior.h"
QMutex VIGeneralBehaviorHost::HOSTMUTEX;
QMutex VIGeneralBehaviorHost::SLEEPMUTEX;
QWaitCondition VIGeneralBehaviorHost::SLEEPWAIT;
VIGeneralBehaviorHost* VIGeneralBehaviorHost::VIGeneralBehaviorHostInstance = new VIGeneralBehaviorHost(qApp);
void VIDuration::init() {
	CURRENT = 0;
	PERCENT = 0;
	PERCENT_NL = 0;
	TIMEOUTFLAG = false;
	LASTTIME = 0;
}
void VIDuration::setDuration(VIMilliSecond msec) {
	if (msec < 0) {
		this->FOREVER = true;
	}
	else {
		this->FOREVER = false;
		
	}
	this->MSEC = msec;
}
double VIDuration::getDuration(Unit unit = Unit::MilliSecond) {
	switch (unit) {
	case Unit::NanoSecond:
		return MSEC * 1000000.0;
	case Unit::MilliSecond:
		return MSEC;
	case Unit::Second:
		return MSEC / 1000.0;
	}
}
float VIDuration::getPercent(PercentType type = PercentType::Linear) {
	switch (type) {
	case PercentType::Linear:
		return PERCENT;
	case PercentType::Nonlinear:
		return PERCENT_NL;
	}
}
VIMilliSecond VIDuration::getCurrent() {
	return CURRENT;
}
VINanoSecond VIDuration::getLastTime() {
	return LASTTIME;
	
}
void VIDuration::setBesselCoeff(VIMath::VI2DMatrix matrix) {
	this->COEFF = matrix;
}
void VIDuration::addTime(unsigned long long time, Unit unit = Unit::MilliSecond) {
	if (!TIMEOUTFLAG) {
		if (!FOREVER) {
			switch (unit) {
			case Unit::NanoSecond:
				this->CURRENT += (float)time / 1000000;
				break;
			case Unit::MilliSecond:
				this->CURRENT += time;
				break;
			case Unit::Second:
				this->CURRENT += time * 1000;
				break;
			}
		}
		switch (unit) {
		case Unit::NanoSecond:
			this->LASTTIME = time;
			break;
		case Unit::MilliSecond:
			this->LASTTIME = time * 1000000;
			break;
		case Unit::Second:
			this->LASTTIME = time * 1000000000;
			break;
		}
		
		PERCENT = (float)CURRENT / MSEC;
		if (PERCENT >= 1) {
			PERCENT = 1;
			emit timeout();
			TIMEOUTFLAG = true;
		}
		PERCENT_NL = VIBessel::getBesselValue(COEFF, PERCENT).y;
	}
}
bool VIDuration::isTimeout() {
	return this->TIMEOUTFLAG;
}

void VIGeneralBehavior::setDuration(VIMilliSecond msec) {
	this->DURATION->setDuration(msec);
}
VIMilliSecond VIGeneralBehavior::getDuration() {
	return this->DURATION->getDuration();
}
float VIGeneralBehavior::getPercent(VIDuration::PercentType type) {
	return this->DURATION->getPercent(type);
}
VIMilliSecond VIGeneralBehavior::getCurrent() {
	return this->DURATION->getCurrent();
}
VIMilliSecond VIGeneralBehavior::getLastTime() {
	return (double)(this->DURATION->getLastTime()) / 1000000;
}
void VIGeneralBehavior::setBesselCoeff(VIMath::VI2DMatrix matrix) {
	return this->DURATION->setBesselCoeff(matrix);
}
void VIGeneralBehavior::setHost(VIGeneralBehaviorHost* host) {
	if (this->HOST != Q_NULLPTR) {
		disconnect(this, SIGNAL(addBehaviorLater(VIGeneralBehavior*)), HOST, SLOT(addBehavior(VIGeneralBehavior*)));
	}
	this->HOST = host;
	connect(this, SIGNAL(addBehaviorLater(VIGeneralBehavior*)), HOST, SLOT(addBehavior(VIGeneralBehavior*)));
}
void VIGeneralBehavior::active() {
	if (STATE == State::Idle) {
		this->DURATION->init();
		this->onActive();
		this->setBehaviorState(State::Active);
		emit addBehaviorLater(this);
	}
}
VIGeneralBehavior::State VIGeneralBehavior::preFrame() {
	this->DURATION->addTime(this->HOST->LASTTIME, VIDuration::Unit::NanoSecond);
	if (DURATION->isTimeout()) {
		this->setBehaviorState(State::Done);
		this->onDone();
		return State::Done;
	}
	else {
		State s = this->getBehaviorState();
		switch(s){
		case State::Active:
			this->onFrame();
			break;
		case State::Skip:
			this->onSkip();
			break;
		case State::Done:
			this->onDone();
			break;
		}
		return s;
	}
}
void VIGeneralBehavior::setBehaviorState(State s) {
	RESMUTEX.lock();
	this->STATE = s;
	RESMUTEX.unlock();
}
VIGeneralBehavior::State VIGeneralBehavior::getBehaviorState() {
	RESMUTEX.lock();
	State s = STATE;
	RESMUTEX.unlock();
	return s;
}
void VIGeneralBehaviorHost::setHostFlag(bool flag) {
	HOSTMUTEX.lock();
	this->HOSTFLAG = flag;
	HOSTMUTEX.unlock();
}
bool VIGeneralBehaviorHost::getHostFlag() {
	HOSTMUTEX.lock();
	bool flag = HOSTFLAG;
	HOSTMUTEX.unlock();
	return flag;
}
void VIGeneralBehaviorHost::run() {
	this->setHostFlag(true);
	while (true) {
		//if (BEHAVIORLIST.isEmpty()) { setSleep(true); SLEEPWAIT.wait(&SLEEPMUTEX); }
		STD_TimePoint TPB = STD_clock_now();
		mergeEvent();
		ergodicEvent();
		if (!getHostFlag()) { break; }
		STD_TimePoint TPE = STD_clock_now();
		LASTTIME = STD_Nano_duration(TPE, TPB);
	}
}
void VIGeneralBehaviorHost::stop() {
	this->setHostFlag(false);
}
void VIGeneralBehaviorHost::mergeEvent() {
	HOSTMUTEX.lock();
	if (!BEHAVIORLIST_ADD.isEmpty()) {
		BEHAVIORLIST.append(BEHAVIORLIST_ADD);
		BEHAVIORLIST_ADD.clear();
	}
	HOSTMUTEX.unlock();
}
void VIGeneralBehaviorHost::ergodicEvent() {
	for (auto i = BEHAVIORLIST.begin(); i != BEHAVIORLIST.end(); ) {
		VIGeneralBehavior::State s = (*i)->preFrame();
		if (s == VIGeneralBehavior::State::Done) {
			(*i)->setBehaviorState(VIGeneralBehavior::State::Idle);
			VIGeneralBehavior* j = (*i);
			i = BEHAVIORLIST.erase(i);
			emit j->done();
		}
		else {
			i++;
		}
	}
}
void VIGeneralBehaviorHost::addBehavior(VIGeneralBehavior* gb) {
	qDebug() << "Add Behavior" << gb;
	HOSTMUTEX.lock();
	BEHAVIORLIST_ADD.append(gb);
	//if (SLEEPFLAG) { SLEEPWAIT.wakeAll(); }
	HOSTMUTEX.unlock();
	qDebug() << "Add Finish";
}

void VIGeneralBehaviorHostDebug::onActive() {
	this->setDuration(-1);
}
void VIGeneralBehaviorHostDebug::onFrame() {
	this->TIME += this->DURATION->getLastTime();
	this->LASTTIME = (this->LASTTIME + this->DURATION->getLastTime()) / 2;
	if (this->TIME > 100000000) {	
		this->FRAME = 1000000000 / this->LASTTIME;
		emit getHostSpeed(this->FRAME);
		this->TIME = 0;
	}
}
void VIGeneralBehaviorHostDebug::onSkip() {
	this->setBehaviorState(VIGeneralBehavior::State::Done);
}
void VIGeneralBehaviorHostDebug::onDone() {
	PASS;
}