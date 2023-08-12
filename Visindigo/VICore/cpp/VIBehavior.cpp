#include "../VIBehavior.h"
#include "../VICoreFramework.h"
#include "../VIConsole.h"
/*
VIBasicBehavior
*/
def_init VIBasicBehavior::VIBasicBehavior(QObject* parent) :VIAbstractBehavior(parent) {
	this->setHost(FrameBehaviorHost);
}

Visindigo::BehaviorState VIBasicBehavior::hostCall() {
	switch (BehaviorState) {
	case Visindigo::Active:
		onTick();
		break;
	case Visindigo::Subside:
		onSubside();
		BehaviorState = Visindigo::Idle;
		break;
	}
	return BehaviorState;
}
void VIBasicBehavior::active(Visindigo::QuantifyTickType type) {
	if (BehaviorState == Visindigo::Idle) {
		BehaviorState = Visindigo::Active;
		onActive();
		this->Host->addBehavior(this, type);
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
void VITimedBehavior::setForeverDuration() {
	Duration->setDuration(VIMilliSecond_MAX);
}
Visindigo::BehaviorState VITimedBehavior::hostCall() {
	VINanoSecond t = getHost()->getTickDuration();
	this->Duration->addTime(t);
	if (Duration->isTimeout()) { BehaviorState = Visindigo::Subside; }
	return VIBasicBehavior::hostCall();
}
void VITimedBehavior::active(Visindigo::QuantifyTickType type) {
	if (BehaviorState == Visindigo::Idle) {
		BehaviorState = Visindigo::Active;
		Duration->initDuration();
		onActive();
		this->Host->addBehavior(this, type);
	}
}
VIMilliSecond VITimedBehavior::getTickDuration() {
	return (float)(dynamic_cast<VIAbstractBehaviorHost*>(getHost())->getTickDuration()) / 1000000.0;
}
/*
VIQuantifyTickBehaviorHost
*/
def_init VIQuantifyTickBehaviorHost::VIQuantifyTickBehaviorHost(VIBehaviorHost* host, VINanoSecond durationLimit, QObject* parent) :VIAbstractBehaviorHost(parent) {
	this->setObjectName("QTickBehaviorHost_" + QString::number((int)1000000000.0 / durationLimit));
	DurationLimit = durationLimit ;
	DurationLimitNow = DurationLimit;
	TickDuration = durationLimit;
	CurrentIndexLeft = 0;
	CurrentIndexRight = 0;
	NSPT = 0;
	NSPTNow = 0;
	DurationNow = 0;
	Host = host;
	Magnification = 1.0;
	consoleLog("Initialized");
	Pause = false;
}
void VIQuantifyTickBehaviorHost::start() {
	throw "VIQuantifyTickBehaviorHost cannot be manually started";
}
void VIQuantifyTickBehaviorHost::pause() {
	Pause = true;
}
void VIQuantifyTickBehaviorHost::resume() {
	Pause = false;
}
void VIQuantifyTickBehaviorHost::stop() {
	throw "VIQuantifyTickBehaviorHost cannot be manually stopped";
}
void VIQuantifyTickBehaviorHost::tickLoop() {
	if (Pause) { return; } //请勿将Pause“优化”为 Magnification == 0.0
	bool LoopFinish = false;
	VINanoSecond t = Host->getTickDuration();
	DurationNow += t * Magnification;
	CurrentIndexRight = BehaviorList.size() * (DurationNow / DurationLimitNow);
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
		if (DurationNow > DurationLimit) {
			DurationLimitNow = 2 * DurationLimit - DurationNow;
			if (DurationLimitNow <= 0) { DurationLimitNow = DurationLimit; }
		}
		else {
			DurationLimitNow = DurationLimit;
		}
		DurationNow = 0;
		NSPT = NSPTNow;
		NSPTNow = 0;
		mergeBehavior();
	}
	else {
		CurrentIndexLeft = CurrentIndexRight;
	}
}
void VIQuantifyTickBehaviorHost::manualTickLoop(VINanoSecond duration) {
	Pause = true;
	bool LoopFinish = false;
	if (duration < 0) {
		duration = DurationLimit;
		DurationNow = DurationLimit;
		CurrentIndexRight = BehaviorList.size();
		LoopFinish = true;
	}
	else {
		DurationNow += duration;
		CurrentIndexRight = BehaviorList.size() * (DurationNow / DurationLimitNow);
		if (CurrentIndexRight >= BehaviorList.size()) {
			CurrentIndexRight = BehaviorList.size();
			LoopFinish = true;
		}
	}
	if (CurrentIndexRight != CurrentIndexLeft) {
		ergodicBehavior();
		NSPTNow += duration;
	}
	if (LoopFinish) {
		CurrentIndexLeft = 0;
		CurrentIndexRight = 0;
		if (DurationNow > DurationLimit) {
			DurationLimitNow = 2 * DurationLimit - DurationNow;
			if (DurationLimitNow < 0) { DurationLimitNow = DurationLimit; }
		}
		else {
			DurationLimitNow = DurationLimit;
		}
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
		if ((*i)->getBehaviorState() == Visindigo::Idle) {
			(*i)->setHost(Host);
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
void VIQuantifyTickBehaviorHost::addBehavior(VIAbstractBehavior* behavior, Visindigo::QuantifyTickType type) {
	BehaviorListAdd.append(behavior);
}
/*
VIBehaviorHost
*/
def_init VIBehaviorHost::VIBehaviorHost(QObject* parent) :VIAbstractBehaviorHost(parent) {
	setObjectName("VIBehaviorHost");
	TickDuration = 10000000;//10ms
	HostDuration = new VIDuration(this);
	STOPFLAG = false;
	QuantifyTickBehaviorHost_128 = new VIQuantifyTickBehaviorHost(this, 7812500, this);
	QuantifyTickBehaviorHost_64 = new VIQuantifyTickBehaviorHost(this, 15625000, this);
	QuantifyTickBehaviorHost_32 = new VIQuantifyTickBehaviorHost(this, 31250000, this);
	QuantifyTickBehaviorHost_20 = new VIQuantifyTickBehaviorHost(this, 50000000, this);
	consoleLog("Initialized");
}
void VIBehaviorHost::start() {
	TickDuration = 10000000;
	qApp->postEvent(this, new QEvent(VIBehaviorLoopEvent::BehaviorLoopEvent));
}
bool VIBehaviorHost::event(QEvent* event) {
	if (event->type() != VIBehaviorLoopEvent::BehaviorLoopEvent) {
		return QObject::event(event);
	}
	tickLoop();
	return true;
}
void VIBehaviorHost::tickLoop() {
	//consoleLog("VIBehaviorHost tickLoop");
	mergeBehavior();
	QuantifyTickBehaviorHost_20->tickLoop();
	QuantifyTickBehaviorHost_32->tickLoop();
	QuantifyTickBehaviorHost_64->tickLoop();
	QuantifyTickBehaviorHost_128->tickLoop();
	ergodicBehavior();
	TickDuration = HostDuration->getNanoDuration();
	//qDebug() << TickDuration;
	if (!STOPFLAG) {
		qApp->postEvent(this, new QEvent(VIBehaviorLoopEvent::BehaviorLoopEvent));
	}
}
void VIBehaviorHost::stop() {
	STOPFLAG = true;
}
void VIBehaviorHost::addBehavior(VIAbstractBehavior* behavior, Visindigo::QuantifyTickType type) {
	switch (type)
	{
	case Visindigo::T0:
		BehaviorListAdd.append(behavior);
		break;
	case Visindigo::T20:
		QuantifyTickBehaviorHost_20->addBehavior(behavior, type);
		break;
	case Visindigo::T32:
		QuantifyTickBehaviorHost_32->addBehavior(behavior, type);
		break;
	case Visindigo::T64:
		QuantifyTickBehaviorHost_64->addBehavior(behavior, type);
		break;
	case Visindigo::T128:
		QuantifyTickBehaviorHost_128->addBehavior(behavior, type);
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
		Visindigo::BehaviorState s = (*i)->hostCall();
		if (s == Visindigo::Idle) {
			i = BehaviorList.erase(i);
		}
		else { i++; }
	}
}

void VIBehaviorHost::setMagnification(double m) {
	QuantifyTickBehaviorHost_20->setMagnification(m);
	QuantifyTickBehaviorHost_32->setMagnification(m);
	QuantifyTickBehaviorHost_64->setMagnification(m);
	QuantifyTickBehaviorHost_128->setMagnification(m);
}
double VIBehaviorHost::getMagnification() {
	return QuantifyTickBehaviorHost_20->getMagnification();
}

void VIBehaviorHost::pauseQuantifyTickBehaviorHost(Visindigo::QuantifyTickType Type) {
	switch (Type)
	{
	case Visindigo::T0:
		QuantifyTickBehaviorHost_128->pause();
		QuantifyTickBehaviorHost_64->pause();
		QuantifyTickBehaviorHost_32->pause();
		QuantifyTickBehaviorHost_20->pause();
		break;
	case Visindigo::T20:
		QuantifyTickBehaviorHost_20->pause();
		break;
	case Visindigo::T32:
		QuantifyTickBehaviorHost_32->pause();
		break;
	case Visindigo::T64:
		QuantifyTickBehaviorHost_64->pause();
		break;
	case Visindigo::T128:
		QuantifyTickBehaviorHost_128->pause();
		break;
	default:
		break;
	}
}
void VIBehaviorHost::resumeQuantifyTickBehaviorHost(Visindigo::QuantifyTickType Type) {
	switch (Type)
	{
	case Visindigo::T0:
		QuantifyTickBehaviorHost_128->resume();
		QuantifyTickBehaviorHost_64->resume();
		QuantifyTickBehaviorHost_32->resume();
		QuantifyTickBehaviorHost_20->resume();
		break;
	case Visindigo::T20:
		QuantifyTickBehaviorHost_20->resume();
		break;
	case Visindigo::T32:
		QuantifyTickBehaviorHost_32->resume();
		break;
	case Visindigo::T64:
		QuantifyTickBehaviorHost_64->resume();
		break;
	case Visindigo::T128:
		QuantifyTickBehaviorHost_128->resume();
		break;
	default:
		break;
	}
}

void VIBehaviorHost::manualExecueQuantifyTickBehaviorHost(Visindigo::QuantifyTickType type, VINanoSecond duration) {
switch (type)
	{
	case Visindigo::T0:
		if (duration < 0) { duration = 7812500; } // if duration < 0, set duration to 1/128 second
		QuantifyTickBehaviorHost_20->manualTickLoop(duration);
		QuantifyTickBehaviorHost_32->manualTickLoop(duration);
		QuantifyTickBehaviorHost_64->manualTickLoop(duration);
		QuantifyTickBehaviorHost_128->manualTickLoop(duration);
		break;
	case Visindigo::T20:
		QuantifyTickBehaviorHost_20->manualTickLoop(duration);
		break;
	case Visindigo::T32:
		QuantifyTickBehaviorHost_32->manualTickLoop(duration);
		break;
	case Visindigo::T64:
		QuantifyTickBehaviorHost_64->manualTickLoop(duration);
		break;
	case Visindigo::T128:
		QuantifyTickBehaviorHost_128->manualTickLoop(duration);
		break;
	}
}
/*
VIDebugBehavior
*/
def_init VIDebugBehavior::VIDebugBehavior(QObject* parent) :VIBasicBehavior(parent) {
	MSPT = 0;
	TMSPT = 0;
	Index = 0;
	consoleLog("VIDebugBehavior init");
}
void VIDebugBehavior::onActive() {
	consoleLog("VIDebugBehavior onActive");
}
void VIDebugBehavior::onSubside() {
	consoleLog("VIDebugBehavior onSubside");
}
#include <iostream>
void VIDebugBehavior::onTick() {
	MSPT += Host->getTickDuration() / 1000000.0;
	TMSPT += ((VIQuantifyTickBehaviorHost*)Host)->getNSPT() / 1000000.0;

	Index++;
	if (Index == 10) {
		std::cout << "                                                                                                   \r" << std::ends;
		std::cout << "  QMSPT: " << QString::number(MSPT / 10.0, 'f', 2).toStdString() << "ms\t  TMSPT:";
		if (TMSPT > 500) {
			std::cout << VIConsole::inErrorStyle(QString::number(TMSPT / 10.0, 'f', 2) + "ms").toStdString();
		}
		else if (TMSPT > 350)
		{
			std::cout << VIConsole::inWarningStyle(QString::number(TMSPT / 10.0, 'f', 2) + "ms").toStdString();
		}
		else if (TMSPT > 250)
		{
			std::cout << VIConsole::inNoticeStyle(QString::number(TMSPT / 10.0, 'f', 2) + "ms").toStdString();
		}
		else {
			std::cout << VIConsole::inSuccessStyle(QString::number(TMSPT / 10.0, 'f', 2) + "ms").toStdString();
		}
		std::cout << "\t  TPS: " << QString::number(10000.0 / MSPT, 'f', 2).toStdString() << "\t  CPUTP: " << QString::number(100 * TMSPT / MSPT, 'f', 2).toStdString() << "%\r" << std::ends;
		Index = 0;
		MSPT = 0;
		TMSPT = 0;
	}
	//qDebug() << Host->getTickDuration()<<((VIQuantifyTickBehaviorHost*)Host)->getNSPT()/1000000.0<<1000000000.0/Host->getTickDuration();
}

void VIAnimationBehavior::active(Visindigo::QuantifyTickType) {
	VITimedBehavior::active(Visindigo::T64);
}

void VIAnimationBehavior::subside() {
	VITimedBehavior::subside();
}