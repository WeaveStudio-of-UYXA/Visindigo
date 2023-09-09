#pragma once
#include "VIAbstractBehavior.h"
#include "VIDuration.h"
class VIPublicAPI VIBehaviorHost;
class VIPublicAPI VIBasicBehavior :public VIAbstractBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIBehaviorHost;
	_Public def_init VIBasicBehavior(QObject* parent = nullptr);
	_Public Visindigo::BehaviorState hostCall();
	_Public void start(Visindigo::QuantifyTickType = Visindigo::T0) override;
};

class VIPublicAPI VITimedBehavior :public VIBasicBehavior
{
	Q_OBJECT;
	friend class VIBehaviorHost;
	VI_Property(VIBehaviorDuration*, Duration);
	_Public def_init VITimedBehavior(QObject* parent = nullptr);
	_Public void setDuration(VIMilliSecond duration);
	_Public void setForeverDuration();
	_Public Visindigo::BehaviorState hostCall();
	_Public void start(Visindigo::QuantifyTickType = Visindigo::T0) override;
	_Public VIMilliSecond getTickDuration();
};
//被动行为
class VIPrivateAPI VIPassiveBehavior :public VIBasicBehavior
{
	Q_OBJECT;
	friend class VIBehaviorHost;
	_Public def_init VIPassiveBehavior(VIAbstractBehavior* parent = nullptr);
	_Public Visindigo::BehaviorState hostCall() override;
	_Public void start(Visindigo::QuantifyTickType = Visindigo::T0) override;
};
class VIPublicAPI VIBehaviorHost;
class VIPublicAPI VIQuantifyTickBehaviorHost final :public VIAbstractBehaviorHost
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
	VI_PrivateFlag(Pause);
	_Public def_init VIQuantifyTickBehaviorHost(VIBehaviorHost* host, VINanoSecond durationLimit, QObject* parent = nullptr);
	_Public void tickLoop() override;
	_Public void manualTickLoop(VINanoSecond duration = -1);
	_Private void mergeBehavior() override;
	_Private void ergodicBehavior() override;
	_Public void start() override;
	_Public void pause();
	_Public void resume();
	_Public void stop() override;
	_Slot void addBehavior(VIAbstractBehavior*, Visindigo::QuantifyTickType) override;
};

class VIPublicAPI VIBehaviorHost final :public VIAbstractBehaviorHost
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
	_Slot void addBehavior(VIAbstractBehavior*, Visindigo::QuantifyTickType) override;
	_Private void mergeBehavior() override;
	_Private void ergodicBehavior() override;
	_Public double getMagnification();
	_Slot void setMagnification(double m);
	_Slot void pauseQuantifyTickBehaviorHost(Visindigo::QuantifyTickType type = Visindigo::T0);
	_Slot void resumeQuantifyTickBehaviorHost(Visindigo::QuantifyTickType type = Visindigo::T0);
	_Slot void manualExecueQuantifyTickBehaviorHost(Visindigo::QuantifyTickType type = Visindigo::T0, VINanoSecond duration = -1);
};

class VIPublicAPI VIDebugBehavior final :public VIBasicBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Property(float, MSPT);
	VI_Property(float, TMSPT);
	VI_Property(int, Index);
	_Public def_init VIDebugBehavior(QObject* parent = nullptr);
	_Public void onStart() override;
	_Public void onTick() override;
	_Public void onStop() override;
};

class VIPublicAPI VIAnimationBehavior :public VITimedBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void finished();
	_Public def_init VIAnimationBehavior(QObject* parent = nullptr) :VITimedBehavior(parent) {}
	_Public void start(Visindigo::QuantifyTickType = Visindigo::T64) override;
	_Public void stop() override;
};