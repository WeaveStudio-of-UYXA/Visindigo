﻿#pragma once
#include "VIObject.h"
#include "private/VIAbstractBehavior_m.h"
#include "VIDuration.h"

class VIAbstractBehaviorHost;
class VIBehaviorHost;
class VIQuantifyTickBehaviorHost;
class VIAbstractBehavior :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIAbstractBehaviorHost;
	friend class VIBehaviorHost;
	friend class VIQuantifyTickBehaviorHost;
	_Public ENUM State{
		Idle,
		Active,
		Passive,
	};
	_Public ENUM QuantifyTickType{
		T0, T20, T32, T64, T128,
	};
	_Public def_init VIAbstractBehavior(VISuper* parent = Q_NULLPTR) :VIObject(parent) {
		Host = Q_NULLPTR; BehaviorState = State::Idle;
	};
	VI_Property(VIAbstractBehaviorHost*, Host);
	VI_Property(State, BehaviorState);
	_Public virtual void onActive()  PureVirtual;
	_Public virtual void onTick()  PureVirtual;
	_Public virtual void onPassive()  PureVirtual;
	_Protected virtual State hostCall()  PureVirtual;
	_Public virtual void active(QuantifyTickType type = QuantifyTickType::T0) PureVirtual;
	_Public void passive();
};

class VIAbstractBehaviorHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIAbstractBehavior;
	_Protected QVector<VIAbstractBehavior*> BehaviorList;
	_Protected QVector<VIAbstractBehavior*> BehaviorListAdd;
	_Protected bool STOPFLAG = false;
	VI_Property(VINanoSecond, TickDuration);
	_Public def_init VIAbstractBehaviorHost(VISuper* parent = VI_NULLPTR) :VIObject(parent) { TickDuration = 0; }
	_Public virtual void start() PureVirtual;
	_Private virtual void tickLoop() PureVirtual;
	_Public virtual void stop() PureVirtual;
	_Slot virtual void addBehavior(VIAbstractBehavior*, VIAbstractBehavior::QuantifyTickType) PureVirtual;
	_Private virtual void mergeBehavior() PureVirtual;
	_Private virtual void ergodicBehavior() PureVirtual;
};

class VIBehaviorLoopEvent :public QEvent
{
	_Public static QEvent::Type BehaviorLoopEvent;
	_Public def_init VIBehaviorLoopEvent() :QEvent(QEvent::Type(QEvent::User + 1)) {};
};