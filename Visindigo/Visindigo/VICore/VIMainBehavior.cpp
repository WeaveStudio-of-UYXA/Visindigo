#include "VIMainBehavior.h"
VIMainBehaviorHost* VIMainBehaviorHost::VIMainBehaviorHostInstance = new VIMainBehaviorHost(qApp);
void VIMainBehavior::setDuration(VIMilliSecond msec) {
	this->DURATION->setDuration(msec);
}
VIMilliSecond VIMainBehavior::getDuration() {
	return this->DURATION->getDuration();
}
float VIMainBehavior::getPercent(VIDuration::PercentType type) {
	return this->DURATION->getPercent(type);
}
VIMilliSecond VIMainBehavior::getCurrent() {
	return this->DURATION->getCurrent();
}
VIMilliSecond VIMainBehavior::getLastTime() {
	return (double)(this->DURATION->getLastTime()) / 1000000;
}
void VIMainBehavior::setBesselCoeff(VIMath::VI2DMatrix matrix) {
	return this->DURATION->setBesselCoeff(matrix);
}
void VIMainBehavior::setHost(VIMainBehaviorHost* host) {
	this->HOST = host;
}
void VIMainBehavior::active() {
	if (STATE == State::Idle) {
		this->DURATION->init();
		this->onActive();
		this->setBehaviorState(State::Active);
		VIMainBehaviorHost::VIMainBehaviorHostInstance->addBehavior(this);
	}
}
VIMainBehavior::State VIMainBehavior::preFrame() {
	this->DURATION->addTime(this->HOST->LASTTIME, VIDuration::Unit::NanoSecond);
	//qDebug() << this->HOST->LASTTIME;
	if (DURATION->isTimeout()) {
		qDebug() << "Behavior Time out";
		this->setBehaviorState(State::Done);
		this->onDone();
		return State::Done;
	}
	else {
		State s = this->getBehaviorState();
		switch (s) {
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
void VIMainBehavior::setBehaviorState(State s) {
	this->STATE = s;
}
VIMainBehavior::State VIMainBehavior::getBehaviorState() {
	return STATE;
}
void VIMainBehaviorHost::start() {
	STOPFLAG = false;
	qApp->postEvent(this, new QEvent(QEvent::None));
}
bool VIMainBehaviorHost::event(QEvent* event) {
	mergeEvent();
	ergodicEvent();	
	STD_TimePoint TPC = STD_clock_now();
	LASTTIME = STD_Nano_duration(TPC, TP);
	TP = TPC;
	if (!STOPFLAG) { qApp->postEvent(this, new QEvent(QEvent::None)); }
	return true;
}
void VIMainBehaviorHost::stop() {
	STOPFLAG = true;
}
void VIMainBehaviorHost::mergeEvent() {
	if (!BEHAVIORLIST_ADD.isEmpty()) {
		BEHAVIORLIST.append(BEHAVIORLIST_ADD);
		BEHAVIORLIST_ADD.clear();
	}
}
void VIMainBehaviorHost::ergodicEvent() {
	for (auto i = BEHAVIORLIST.begin(); i != BEHAVIORLIST.end(); ) {
		VIMainBehavior::State s = (*i)->preFrame();
		if (s == VIMainBehavior::State::Done) {
			qDebug() << "Remove Behavior" << *i;
			(*i)->setBehaviorState(VIMainBehavior::State::Idle);
			VIMainBehavior* j = (*i);
			i = BEHAVIORLIST.erase(i);
			emit j->done();
		}
		else {
			i++;
		}
	}
}
void VIMainBehaviorHost::addBehavior(VIMainBehavior* gb) {
	qDebug() << "Add Behavior" << gb;
	BEHAVIORLIST_ADD.append(gb);
	//if (SLEEPFLAG) { SLEEPWAIT.wakeAll(); }
	qDebug() << "Add Finish";
}

void VIMainBehaviorHostDebug::onActive() {
	this->setDuration(-1);
}
void VIMainBehaviorHostDebug::onFrame() {
	this->TIME += this->DURATION->getLastTime();
	this->LASTTIME = (this->LASTTIME + this->DURATION->getLastTime()) / 2;
	if (this->TIME > 100000000) {
		this->FRAME = 1000000000 / this->LASTTIME;
		emit getHostSpeed(this->FRAME);
		this->TIME = 0;
	}
}
void VIMainBehaviorHostDebug::onSkip() {
	this->setBehaviorState(VIMainBehavior::State::Done);
}
void VIMainBehaviorHostDebug::onDone() {
	PASS;
}