#pragma once
#include "VIObject.h"
#include "private/VIAbstractBehavior_m.h"
#include "VIDuration.h"

class VIPublicAPI VIAbstractBehaviorHost;
class VIPublicAPI VIBehaviorHost;
class VIPublicAPI VIQuantifyTickBehaviorHost;

class VIPublicAPI VIAbstractBehavior :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIAbstractBehaviorHost;
	friend class VIBehaviorHost;
	friend class VIQuantifyTickBehaviorHost;
	_Public def_init VIAbstractBehavior(VISuper* parent = Q_NULLPTR) :VIObject(parent) {
		Host = Q_NULLPTR; BehaviorState = Visindigo::BehaviorState::Idle;
	};
	VI_Property(VIAbstractBehaviorHost*, Host);
	VI_Property(Visindigo::BehaviorState, BehaviorState);
	_Public virtual void onActive()  PureVirtual;
	_Public virtual void onTick()  PureVirtual;
	_Public virtual void onSubside()  PureVirtual;
	_Protected virtual Visindigo::BehaviorState hostCall()  PureVirtual;
	_Public virtual void active(Visindigo::QuantifyTickType type = Visindigo::T0) PureVirtual;
	_Public virtual void subside();
};

class VIPublicAPI VIAbstractBehaviorHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIAbstractBehavior;
	_Protected QVector<VIAbstractBehavior*> BehaviorList;
	_Protected QVector<VIAbstractBehavior*> BehaviorListAdd;
	_Protected bool STOPFLAG = false;
	VI_ProtectedProperty(VINanoSecond, TickDuration);
	_Public def_init VIAbstractBehaviorHost(VISuper* parent = VI_NULLPTR) :VIObject(parent) { TickDuration = 0; }
	_Public virtual void start() PureVirtual;
	_Private virtual void tickLoop() PureVirtual;
	_Public virtual void stop() PureVirtual;
	_Slot virtual void addBehavior(VIAbstractBehavior*, Visindigo::QuantifyTickType) PureVirtual;
	_Private virtual void mergeBehavior() PureVirtual;
	_Private virtual void ergodicBehavior() PureVirtual;
};

class VIPublicAPI VIBehaviorLoopEvent :public QEvent
{
	_Public static QEvent::Type BehaviorLoopEvent;
	_Public def_init VIBehaviorLoopEvent() :QEvent(QEvent::Type(QEvent::User + 1)) {};
};