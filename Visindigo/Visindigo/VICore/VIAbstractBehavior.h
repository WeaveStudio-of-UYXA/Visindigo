#pragma once
#include "VIObject.h"
#include "macro/VIGeneralBehavior_m.h"
class VIAbstractBehaviorHost;
class VIBehaviorHost;
class VIAbstractBehavior :public QObject, VIObject
{
	VI_OBJECT;
	friend class VIAbstractBehaviorHost;
	friend class VIBehaviorHost;
	_Public ENUM State{
		Idle,
		Active,
		Passive,
	};
	_Public def_init VIAbstractBehavior(QObject* parent = Q_NULLPTR) :QObject(parent) { 
		Host = Q_NULLPTR; BehaviorState = State::Idle;
	};
	VI_Property(VIAbstractBehaviorHost*, Host);
	VI_Property(State, BehaviorState);
	_Public virtual void onActive()  PureVirtual;
	_Public virtual void onTick()  PureVirtual;
	_Public virtual void onPassive()  PureVirtual;
	_Protected virtual State hostCall()  PureVirtual;
	_Public virtual void active() PureVirtual;
	_Public virtual void passive() PureVirtual;
};

class VIAbstractBehaviorHost :public QObject
{
	Q_OBJECT;
	friend class VIAbstractBehavior;
	_Public static VIAbstractBehaviorHost* HostInstance;
	_Protected QVector<VIAbstractBehavior*> BehaviorList;
	_Protected QVector<VIAbstractBehavior*> BehaviorListAdd;
	_Protected bool STOPFLAG = false;
	_Public def_init VIAbstractBehaviorHost(QObject* parent = Q_NULLPTR) :QObject(parent) {}
	_Public virtual void start() PureVirtual;
	_Private virtual void tickLoop() PureVirtual;
	_Public virtual void stop() PureVirtual;
	_Slot virtual void addBehavior(VIAbstractBehavior*) PureVirtual;
	_Private virtual void mergeEvent() PureVirtual;
	_Private virtual void ergodicEvent() PureVirtual;
};