#include "VIBehavior.h"
#include "VIFramework.h"
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
	Duration->setDuration(duration*1000000);
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
	return (float)(dynamic_cast<VIBehaviorHost*>(getHost())->getTickDuration())/1000000.0;
}
/*
VIBehaviorHost
*/
def_init VIBehaviorHost::VIBehaviorHost(QObject* parent) :VIAbstractBehaviorHost(parent) {
	TickDuration = 10000000;//10ms
	HostDuration = new VIDuration();
}
void VIBehaviorHost::start() {
	TickDuration = HostDuration->getNanoDuration();
	qApp->postEvent(this, new QEvent(QEvent::None));
}
bool VIBehaviorHost::event(QEvent* event) {
	tickLoop();
	return true;
}
void VIBehaviorHost::tickLoop() {
	mergeBehavior();
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