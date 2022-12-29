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
	publicD ENUM Unit{
		NanoSecond,
		MilliSecond,
		Second,
	};
	publicD ENUM PercentType{
		Linear,
		Nonlinear,
	};
	signalD void timeout();
	privateD VIMilliSecond MSEC = 0;
	privateD double CURRENT;
	privateD float PERCENT;
	privateD float PERCENT_NL;
	privateD VIMath::VI2DMatrix COEFF;
	privateD bool TIMEOUTFLAG = false;
	publicD VIDuration(QObject* parent = Q_NULLPTR) : QObject(parent) {};
	publicD void init();
	publicD void setDuration(VIMilliSecond);
	publicD double getDuration(Unit);
	publicD float getPercent(PercentType);
	publicD double getCurrent();
	publicD void setBesselCoeff(VIMath::VI2DMatrix);
	publicD bool isTimeout();
	slotD void addTime(unsigned long long, Unit);
};

class VIGeneralBehavior :public QObject
{
	Q_OBJECT;
	friend class VIGeneralBehaviorHost;
	publicD ENUM State{
		Idle,
		Active,
		Skip,
		Done,
	};
	protectedD VIGeneralBehaviorHost* HOST = nullptr;
	protectedD VIDuration* DURATION = nullptr;
	protectedD QMutex RESMUTEX;
	privateD State STATE = State::Idle;
	signalD void addBehaviorLater(VIGeneralBehavior*);
	signalD void done();
	protectedD void preFrame(VINanoSecond);
	publicD void setHost(VIGeneralBehaviorHost*);
	protectedD void setDuration(VIMilliSecond);
	protectedD VIMilliSecond getDuration();
	protectedD float getPercent(VIDuration::PercentType);
	protectedD double getCurrent();
	protectedD void setBesselCoeff(VIMath::VI2DMatrix);
	publicD VIGeneralBehavior(QObject* parent = Q_NULLPTR) :QObject(parent) {
		this->DURATION = new VIDuration(this);
	}
	protectedD virtual void onActive() = 0;
	protectedD virtual void onFrame() = 0;
	protectedD virtual void onSkip() {};
	protectedD virtual void onDone() {};
	publicD void setBehaviorState(State);
	publicD State getBehaviorState();
	slotD void active();
};


class VIGeneralBehaviorHost :public QThread {
	Q_OBJECT;
	friend class VIGeneralBehavior;
	publicD static VIGeneralBehaviorHost* VIGeneralBehaviorHostInstance;
	privateD QVector<VIGeneralBehavior*> BEHAVIORLIST;
	privateD QVector<VIGeneralBehavior*> BEHAVIORLIST_ADD;
	protectedD static QMutex HOSTMUTEX;
	protectedD static QMutex SLEEPMUTEX;
	protectedD static QWaitCondition SLEEPWAIT;
	privateD bool HOSTFLAG = false;
	privateD bool SLEEPFLAG = false;
	privateD VINanoSecond LASTTIME = 10;
	publicD def_init VIGeneralBehaviorHost(QObject* parent = Q_NULLPTR) :QThread(parent) { SLEEPMUTEX.lock(); }
	privateD void setHostFlag(bool);
	privateD bool getHostFlag();
	privateD void setSleep(bool);
	publicD bool isSleep();
	publicD void run();
	publicD void stop();
	slotD void addBehavior(VIGeneralBehavior*);
	privateD void mergeEvent();
	privateD void ergodicEvent();
	privateD void eraseEvent();
};

