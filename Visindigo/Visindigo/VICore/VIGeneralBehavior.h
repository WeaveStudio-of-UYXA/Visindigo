/*
此文件用于实现Visindigo2D的总动画效果和内部事件队列
实际上对于Qt的2D动画，只需要使用QPropertyAnimation即可
或者选择使用QPropertyAnimation的子类QVariantAnimation
此文档的意义在于针对Visindigo本身的需求提供一个在动画上相对通用的队列处理系统
*/
#pragma once
#include<QtCore>
#include<QtWidgets>
#include <chrono>
#include "VIMath.h"
#include "../../CommonEdit/CECore/CEMacro.h"
#include "macro/VIGeneralBehavior_m.h"

class VIDuration :public QObject
{
	Q_OBJECT;
	_Public ENUM Unit{
		NanoSecond,
		MilliSecond,
		Second,
	};
	_Public ENUM PercentType{
		Linear,
		Nonlinear,
	};
	_Signal void timeout();
	_Private VIMilliSecond MSEC = 0;
	_Protected bool FOREVER = false;
	_Private double CURRENT;
	_Private float PERCENT;
	_Private float PERCENT_NL;
	_Private VINanoSecond LASTTIME;
	_Private VIMath::VI2DMatrix COEFF = { {0, 0}, {1, 1} };
	_Private bool TIMEOUTFLAG = false;
	_Public VIDuration(QObject* parent = Q_NULLPTR) : QObject(parent) {};
	_Public void init();
	_Public void setDuration(VIMilliSecond);
	_Public double getDuration(Unit);
	_Public float getPercent(PercentType);
	_Public VIMilliSecond getCurrent();
	_Public VINanoSecond getLastTime();
	_Public void setBesselCoeff(VIMath::VI2DMatrix);
	_Public bool isTimeout();
	_Slot void addTime(unsigned long long, Unit);
};

class VIGeneralBehaviorHost;
class VIGeneralBehavior :public QObject
{
	Q_OBJECT;
	friend class VIGeneralBehaviorHost;
	_Public ENUM State{
		Idle,
		Active,
		Skip,
		Done,
	};
	_Protected VIGeneralBehaviorHost* HOST = nullptr;
	_Protected VIDuration* DURATION = nullptr;
	_Protected QMutex RESMUTEX;
	_Private State STATE = State::Idle;
	_Signal void addBehaviorLater(VIGeneralBehavior*);
	_Signal void done();
	_Protected State preFrame();
	_Public void setHost(VIGeneralBehaviorHost*);
	_Protected void setDuration(VIMilliSecond);
	_Protected VIMilliSecond getDuration();
	_Protected float getPercent(VIDuration::PercentType);
	_Protected VIMilliSecond getCurrent();
	_Protected VIMilliSecond getLastTime();
	_Public void setBesselCoeff(VIMath::VI2DMatrix);
	_Public def_init VIGeneralBehavior(QObject* parent = Q_NULLPTR) :QObject(parent) {
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


class VIGeneralBehaviorHost :public QThread {
	Q_OBJECT;
	friend class VIGeneralBehavior;
	_Public static VIGeneralBehaviorHost* VIGeneralBehaviorHostInstance;
	_Private QVector<VIGeneralBehavior*> BEHAVIORLIST;
	_Private QVector<VIGeneralBehavior*> BEHAVIORLIST_ADD;
	_Protected static QMutex HOSTMUTEX;
	_Protected static QMutex SLEEPMUTEX;
	_Protected static QWaitCondition SLEEPWAIT;
	_Private bool HOSTFLAG = false;
	_Private bool SLEEPFLAG = false;
	_Private VINanoSecond LASTTIME = 10;
	_Public def_init VIGeneralBehaviorHost(QObject* parent = Q_NULLPTR) :QThread(parent) { SLEEPMUTEX.lock(); }
	_Private void setHostFlag(bool);
	_Private bool getHostFlag();
	_Public void run();
	_Public void stop();
	_Slot void addBehavior(VIGeneralBehavior*);
	_Private void mergeEvent();
	_Private void ergodicEvent();
	_Private void eraseEvent();
};

class VIGeneralBehaviorHostDebug final :public VIGeneralBehavior
{
	Q_OBJECT;
	_Public VINanoSecond LASTTIME = 10;
	_Public unsigned int FRAME = 0;
	_Public VINanoSecond TIME = 0;
	_Public def_init VIGeneralBehaviorHostDebug(QObject* parent = Q_NULLPTR) :VIGeneralBehavior(parent) {}
	_Signal void getHostSpeed(unsigned int);
	_Public void onActive();
	_Public void onFrame();
	_Public void onSkip();
	_Public void onDone();
};