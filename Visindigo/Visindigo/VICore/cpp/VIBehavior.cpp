#include "../VIBehavior.h"
#include "../VIFramework.h"
/*
VIBasicBehavior
*/
def_init VIBasicBehavior::VIBasicBehavior(QObject* parent) :VIAbstractBehavior(parent) {
	this->setHost(FrameBehaviorHost);
}

VIAbstractBehavior::State VIBasicBehavior::hostCall() {
	switch (BehaviorState) {
	case State::Active:
		onTick();
		break;
	case State::Passive:
		onPassive();
		BehaviorState = State::Idle;
		break;
	}
	return BehaviorState;
}
void VIBasicBehavior::active() {
	if (BehaviorState == State::Idle) {
		BehaviorState = State::Active;
		onActive();
		this->Host->addBehavior(this);
	}
}


/*
VITimedBehavior
*/
def_init VITimedBehavior::VITimedBehavior(QObject* parent) :VIBasicBehavior(parent) {
	Duration = new VIBehaviorDuration(this);
}
void VITimedBehavior::setDuration(VIMilliSecond duration) {
	Duration->setDuration(duration * 1000000);
}
VIAbstractBehavior::State VITimedBehavior::hostCall() {
	VINanoSecond t = dynamic_cast<VIBehaviorHost*>(getHost())->getTickDuration();
	this->Duration->addTime(t);
	//qDebug() << t;
	if (Duration->isTimeout()) { BehaviorState = State::Passive; }
	return VIBasicBehavior::hostCall();
}
void VITimedBehavior::active() {
	if (BehaviorState == State::Idle) {
		BehaviorState = State::Active;
		Duration->initDuration();
		onActive();
		this->Host->addBehavior(this);
	}
}
VIMilliSecond VITimedBehavior::getTickDuration() {
	return (float)(dynamic_cast<VIBehaviorHost*>(getHost())->getTickDuration()) / 1000000.0;
}
/*
VIQuantifyTickBehaviorHost
*/
def_init VIQuantifyTickBehaviorHost::VIQuantifyTickBehaviorHost(VIBehaviorHost* host, VINanoSecond durationLimit, QObject* parent) :VIAbstractBehaviorHost(parent) {
	DurationLimit = durationLimit;
	TickDuration = durationLimit;
	CurrentIndexLeft = 0;
	CurrentIndexRight = 0;
	NSPT = 0;
	NSPTNow = 0;
	DurationNow = 0;
	Host = host;
	consoleLog("VIQuantifyTickBehaviorHost init :" + QString::number(DurationLimit));
}
void VIQuantifyTickBehaviorHost::start() {
	throw "VIQuantifyTickBehaviorHost cannot be manually started";
}
void VIQuantifyTickBehaviorHost::stop() {
	throw "VIQuantifyTickBehaviorHost cannot be manually stopped";
}
void VIQuantifyTickBehaviorHost::tickLoop() {
	bool LoopFinish = false;
	VINanoSecond t = Host->getTickDuration();
	DurationNow += t;
	CurrentIndexRight = BehaviorList.size() * (DurationNow / DurationLimit);
	if (CurrentIndexRight >= BehaviorList.size()) {
		CurrentIndexRight = BehaviorList.size();
		LoopFinish = true;
	}
	if (CurrentIndexRight != CurrentIndexLeft) {
		ergodicBehavior();
		NSPTNow += t;
	}
	if (LoopFinish) {
		CurrentIndexLeft = 0;
		CurrentIndexRight = 0;
		TickDuration = DurationNow;
		DurationNow = 0;
		NSPT = NSPTNow;
		NSPTNow = 0;
		mergeBehavior();
	}
	else {
		CurrentIndexLeft = CurrentIndexRight;
	}
}
void VIQuantifyTickBehaviorHost::mergeBehavior() {
	for (auto i = BehaviorList.begin(); i != BehaviorList.end();) {
		if ((*i)->getBehaviorState() == VIAbstractBehavior::State::Idle) {
			i = BehaviorList.erase(i);
		}
		else { i++; }
	}
	if (!BehaviorListAdd.isEmpty()) {
		for (auto i = BehaviorListAdd.begin(); i != BehaviorListAdd.end(); i++) {
			BehaviorList.append(*i);
			(*i)->setHost(this);
		}
		BehaviorListAdd.clear();
	}
}
void VIQuantifyTickBehaviorHost::ergodicBehavior() {
	for (auto i = CurrentIndexLeft; i != CurrentIndexRight; i++) {
		BehaviorList[i]->hostCall();
	}
}
void VIQuantifyTickBehaviorHost::addBehavior(VIAbstractBehavior* behavior) {
	BehaviorListAdd.append(behavior);
}
/*
VIBehaviorHost
*/
def_init VIBehaviorHost::VIBehaviorHost(QObject* parent) :VIAbstractBehaviorHost(parent) {
	consoleLog("VIBehaviorHost init");
	TickDuration = 10000000;//10ms
	HostDuration = new VIDuration(this);
	STOPFLAG = false;
	QuantifyTickBehaviorHost_64 = new VIQuantifyTickBehaviorHost(this, 15625000, this);
	QuantifyTickBehaviorHost_20 = new VIQuantifyTickBehaviorHost(this, 50000000, this);
}
void VIBehaviorHost::start() {
	TickDuration = 10000000;
	qApp->postEvent(this, new QEvent(QEvent::None));
}
bool VIBehaviorHost::event(QEvent* event) {
	tickLoop();
	return true;
}
void VIBehaviorHost::tickLoop() {
	consoleLog("VIBehaviorHost tickLoop");
	mergeBehavior();
	QuantifyTickBehaviorHost_20->tickLoop();
	QuantifyTickBehaviorHost_64->tickLoop();
	ergodicBehavior();
	TickDuration = HostDuration->getNanoDuration();
	//qDebug() << TickDuration;
	if (!STOPFLAG) {
		qApp->postEvent(this, new QEvent(QEvent::None));
	}
}
void VIBehaviorHost::stop() {
	STOPFLAG = true;
}
void VIBehaviorHost::addBehavior(VIAbstractBehavior* behavior) {
	BehaviorListAdd.append(behavior);
}
void VIBehaviorHost::addQuantifyTickBehavior(VIAbstractBehavior* behavior, QuantifyTickType type) {
	switch (type)
	{
	case VIBehaviorHost::QuantifyTickType::T20:
		QuantifyTickBehaviorHost_20->addBehavior(behavior);
		break;
	case VIBehaviorHost::QuantifyTickType::T64:
		QuantifyTickBehaviorHost_64->addBehavior(behavior);
		break;
	}
}
void VIBehaviorHost::mergeBehavior() {
	if (!BehaviorListAdd.isEmpty()) {
		BehaviorList.append(BehaviorListAdd);
		BehaviorListAdd.clear();
	}
}
void VIBehaviorHost::ergodicBehavior() {
	for (auto i = BehaviorList.begin(); i != BehaviorList.end();) {
		VIAbstractBehavior::State s = (*i)->hostCall();
		if (s == VIAbstractBehavior::State::Idle) {
			i = BehaviorList.erase(i);
		}
		else { i++; }
	}
}