#pragma once
#include "VIAbstractBehavior.h"
#include "VIDuration.h"
#define BehaviorHost VIBehaviorHost::HostInstance
class VIBehaviorHost;
class VIBasicBehavior :public VIAbstractBehavior
{
	Q_OBJECT;
	friend class VIBehaviorHost;
	_Public def_init VIBasicBehavior(QObject* parent = nullptr);
	_Public State hostCall();
	_Public void active() override;
	_Public void passive() override;
};

class VITimedBehavior :public VIBasicBehavior
{
	Q_OBJECT;
	friend class VIBehaviorHost;
	VI_Property(VIBehaviorDuration*, Duration);
	_Public def_init VITimedBehavior(QObject* parent = nullptr);
	_Public void setDuration(VIMilliSecond duration);
	_Public State hostCall();
	_Public void active() override;
	_Public VIMilliSecond getTickDuration();
};

class VIBehaviorHost :public VIAbstractBehaviorHost
{
	Q_OBJECT;
	friend class VIBasicBehavior;
	friend class VITimedBehavior;
	_Public VITime* HostTime;
	VI_Property(VINanoSecond, TickDuration);
	_Public def_init VIBehaviorHost(QObject* parent = nullptr);
	_Public void start() override;
	_Public bool event(QEvent* event) override;
	_Private void tickLoop() override;
	_Public void stop() override;
	_Slot void addBehavior(VIAbstractBehavior*) override;
	_Private void mergeEvent() override;
	_Private void ergodicEvent() override;
};
