#pragma once
#include "VIAbstractBehavior.h"
#include "VIDuration.h"
class VIBehaviorHost;
class VIBasicBehavior :public VIAbstractBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIBehaviorHost;
	_Public def_init VIBasicBehavior(QObject* parent = nullptr);
	_Public State hostCall();
	_Public void active() override;
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

class VIQuantifyTickBehaviorHost final :public VIAbstractBehaviorHost
{
	Q_OBJECT;
	friend class VIBehaviorHost;
	_Public def_init VIQuantifyTickBehaviorHost(QObject* parent = nullptr);
	_Private void tickLoop() override;
	_Private void mergeBehavior() override;
	_Private void ergodicBehavior() override;
};

class VIBehaviorHost :public VIAbstractBehaviorHost
{
	Q_OBJECT;
	friend class VIBasicBehavior;
	friend class VITimedBehavior;
	_Public VIDuration* HostDuration;
	VI_Property(VINanoSecond, TickDuration);
	_Public def_init VIBehaviorHost(QObject* parent = nullptr);
	_Public void start() override;
	_Public bool event(QEvent* event) override;
	_Private void tickLoop() override;
	_Public void stop() override;
	_Slot void addBehavior(VIAbstractBehavior*) override;
	_Slot void addQuantifyTickBehavior(VIAbstractBehavior*);
	_Private void mergeBehavior() override;
	_Private void ergodicBehavior() override;
};
