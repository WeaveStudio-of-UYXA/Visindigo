#pragma once
#include "VIGeneralBehavior.h"

//此文件旨在提供一个与Qt事件机制绑定的VI事件队列。
//此事件队列只能在主线程中使用，并且由Visindigo自动创建唯一实例，用户不要进行任何操作。

class VIMainBehaviorHost;
class VIMainBehavior :public QObject
{
	Q_OBJECT;
	friend class VIMainBehaviorHost;
	_Public ENUM State{
		Idle,
		Active,
		Skip,
		Done,
	};
	_Protected VIMainBehaviorHost* HOST = nullptr;
	_Protected VIDuration* DURATION = nullptr;
	_Private State STATE = State::Idle;
	_Signal void done();
	_Protected State preFrame();
	_Public void setHost(VIMainBehaviorHost*);
	_Protected void setDuration(VIMilliSecond);
	_Protected VIMilliSecond getDuration();
	_Protected float getPercent(VIDuration::PercentType);
	_Protected VIMilliSecond getCurrent();
	_Protected VIMilliSecond getLastTime();
	_Public void setBesselCoeff(VIMath::VI2DMatrix);
	_Public def_init VIMainBehavior(QObject* parent = Q_NULLPTR) :QObject(parent) {
		this->DURATION = new VIDuration(this);
	}
	_Protected virtual void onActive() = 0;
	_Protected virtual void onFrame() = 0;
	_Protected virtual void onSkip() {};
	_Protected virtual void onDone() {};
	_Public void setBehaviorState(State);
	_Public State getBehaviorState();
	_Slot void active();
};

class VIMainBehaviorHost :public QObject{
	Q_OBJECT;
	friend class VIMainBehavior;
	_Public static VIMainBehaviorHost* VIMainBehaviorHostInstance;
	_Private QVector<VIMainBehavior*> BEHAVIORLIST;
	_Private QVector<VIMainBehavior*> BEHAVIORLIST_ADD;
	_Private bool STOPFLAG = false;
	_Private VINanoSecond LASTTIME = 10;
	_Public STD_TimePoint TP;
	_Public def_init VIMainBehaviorHost(QObject* parent = Q_NULLPTR) :QObject(parent) {}
	_Slot void start();
	_Public bool event(QEvent* event);
	_Public void stop();
	_Slot void addBehavior(VIMainBehavior*);
	_Private void mergeEvent();
	_Private void ergodicEvent();
};

class VIMainBehaviorHostDebug final :public VIMainBehavior
{
	Q_OBJECT;
	_Public VINanoSecond LASTTIME = 10;
	_Public unsigned int FRAME = 0;
	_Public VINanoSecond TIME = 0;
	_Public def_init VIMainBehaviorHostDebug(QObject* parent = Q_NULLPTR) :VIMainBehavior(parent) {}
	_Signal void getHostSpeed(unsigned int);
	_Public void onActive();
	_Public void onFrame();
	_Public void onSkip();
	_Public void onDone();
};