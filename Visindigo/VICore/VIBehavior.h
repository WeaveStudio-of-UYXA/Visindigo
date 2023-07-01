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
	_Public void active(VIAbstractBehavior::QuantifyTickType = QuantifyTickType::T0) override;
};

class VITimedBehavior :public VIBasicBehavior
{
	Q_OBJECT;
	friend class VIBehaviorHost;
	VI_Property(VIBehaviorDuration*, Duration);
	_Public def_init VITimedBehavior(QObject* parent = nullptr);
	_Public void setDuration(VIMilliSecond duration);
	_Public void setForeverDuration();
	_Public State hostCall();
	_Public void active(VIAbstractBehavior::QuantifyTickType = QuantifyTickType::T0) override;
	_Public VIMilliSecond getTickDuration();
};
//被动行为
class VIPassiveBehavior :public VIBasicBehavior
{
	Q_OBJECT;
	friend class VIBehaviorHost;
	_Public def_init VIPassiveBehavior(QObject* parent = nullptr);
};
class VIBehaviorHost;
class VIQuantifyTickBehaviorHost final :public VIAbstractBehaviorHost
{
	Q_OBJECT;
	friend class VIBasicBehavior;
	friend class VITimedBehavior;
	friend class VIBehaviorHost;
	_Private VIBehaviorHost* Host;
	VI_Property(VINanoSecond, DurationNow);
	VI_Property(VINanoSecond, NSPT);
	VI_ProtectedProperty(double, Magnification);
	VI_PrivateProperty(VINanoSecond, NSPTNow);
	VI_PrivateProperty(VINanoSecond, DurationLimit);
	VI_PrivateProperty(VINanoSecond, DurationLimitNow);
	VI_PrivateProperty(unsigned long long, CurrentIndexLeft);
	VI_PrivateProperty(unsigned long long, CurrentIndexRight);
	VI_PrivateFlag(Pause)
	_Public def_init VIQuantifyTickBehaviorHost(VIBehaviorHost* host, VINanoSecond durationLimit, QObject* parent = nullptr);
	_Public void tickLoop() override;
	_Private void mergeBehavior() override;
	_Private void ergodicBehavior() override;
	_Public void start() override;
	_Public void pause();
	_Public void resume();
	_Public void stop() override;
	_Slot void addBehavior(VIAbstractBehavior*, VIAbstractBehavior::QuantifyTickType) override;
};

class VIBehaviorHost final :public VIAbstractBehaviorHost
{
	Q_OBJECT;
	friend class VIBasicBehavior;
	friend class VITimedBehavior;
	_Public VIDuration* HostDuration = nullptr;
	_Private VIQuantifyTickBehaviorHost* QuantifyTickBehaviorHost_128;
	_Private VIQuantifyTickBehaviorHost* QuantifyTickBehaviorHost_64;
	_Private VIQuantifyTickBehaviorHost* QuantifyTickBehaviorHost_32;
	_Private VIQuantifyTickBehaviorHost* QuantifyTickBehaviorHost_20;
	_Public def_init VIBehaviorHost(QObject* parent = nullptr);
	_Public void start() override;
	_Public bool event(QEvent* event) override;
	_Private void tickLoop() override;
	_Public void stop() override;
	_Slot void addBehavior(VIAbstractBehavior*, VIAbstractBehavior::QuantifyTickType) override;
	_Private void mergeBehavior() override;
	_Private void ergodicBehavior() override;
	_Public double getMagnification();
	_Public void setMagnification(double m);
	_Public void pauseQuantifyTickBehaviorHost(VIAbstractBehavior::QuantifyTickType type = VIAbstractBehavior::QuantifyTickType::T0);
	_Public void resumeQuantifyTickBehaviorHost(VIAbstractBehavior::QuantifyTickType type = VIAbstractBehavior::QuantifyTickType::T0);
};

class VIDebugBehavior final :public VIBasicBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Property(float, MSPT);
	VI_Property(float, TMSPT);
	VI_Property(int, Index);
	_Public def_init VIDebugBehavior(QObject* parent = nullptr);
	_Public void onActive() override;
	_Public void onTick() override;
	_Public void onSubside() override;
};

class VIAnimationBehavior :public VITimedBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void finished();
	_Public def_init VIAnimationBehavior(QObject* parent = nullptr) :VITimedBehavior(parent) {}
	_Public void active(VIAbstractBehavior::QuantifyTickType = QuantifyTickType::T64) override {
		VITimedBehavior::active(QuantifyTickType::T64);
	}
};