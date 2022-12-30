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
	Public_ ENUM Unit{
		NanoSecond,
		MilliSecond,
		Second,
	};
	Public_ ENUM PercentType{
		Linear,
		Nonlinear,
	};
	Signal_ void timeout();
	Private_ VIMilliSecond MSEC = 0;
	Protected_ bool FOREVER = false;
	Private_ double CURRENT;
	Private_ float PERCENT;
	Private_ float PERCENT_NL;
	Private_ VIMath::VI2DMatrix COEFF = { {0, 0}, {1, 1} };
	Private_ bool TIMEOUTFLAG = false;
	Public_ VIDuration(QObject* parent = Q_NULLPTR) : QObject(parent) {};
	Public_ void init();
	Public_ void setDuration(VIMilliSecond);
	Public_ double getDuration(Unit);
	Public_ float getPercent(PercentType);
	Public_ double getCurrent();
	Public_ void setBesselCoeff(VIMath::VI2DMatrix);
	Public_ bool isTimeout();
	Slot_ void addTime(unsigned long long, Unit);
};

class VIGeneralBehavior :public QObject
{
	Q_OBJECT;
	friend class VIGeneralBehaviorHost;
	Public_ ENUM State{
		Idle,
		Active,
		Skip,
		Done,
	};
	Protected_ VIGeneralBehaviorHost* HOST = nullptr;
	Protected_ VIDuration* DURATION = nullptr;
	Protected_ QMutex RESMUTEX;
	Private_ State STATE = State::Idle;
	Signal_ void addBehaviorLater(VIGeneralBehavior*);
	Signal_ void done();
	Protected_ void preFrame(VINanoSecond);
	Public_ void setHost(VIGeneralBehaviorHost*);
	Protected_ void setDuration(VIMilliSecond);
	Protected_ VIMilliSecond getDuration();
	Protected_ float getPercent(VIDuration::PercentType);
	Protected_ double getCurrent();
	Public_ void setBesselCoeff(VIMath::VI2DMatrix);
	Public_ VIGeneralBehavior(QObject* parent = Q_NULLPTR) :QObject(parent) {
		this->DURATION = new VIDuration(this);
	}
	Protected_ virtual void onActive() = 0;
	Protected_ virtual void onFrame() = 0;
	Protected_ virtual void onSkip() {};
	Protected_ virtual void onDone() {};
	Public_ void setBehaviorState(State);
	Public_ State getBehaviorState();
	Slot_ void active();
};


class VIGeneralBehaviorHost :public QThread {
	Q_OBJECT;
	friend class VIGeneralBehavior;
	Public_ static VIGeneralBehaviorHost* VIGeneralBehaviorHostInstance;
	Private_ QVector<VIGeneralBehavior*> BEHAVIORLIST;
	Private_ QVector<VIGeneralBehavior*> BEHAVIORLIST_ADD;
	Protected_ static QMutex HOSTMUTEX;
	Protected_ static QMutex SLEEPMUTEX;
	Protected_ static QWaitCondition SLEEPWAIT;
	Private_ bool HOSTFLAG = false;
	Private_ bool SLEEPFLAG = false;
	Private_ VINanoSecond LASTTIME = 10;
	Public_ def_init VIGeneralBehaviorHost(QObject* parent = Q_NULLPTR) :QThread(parent) { SLEEPMUTEX.lock(); }
	Private_ void setHostFlag(bool);
	Private_ bool getHostFlag();
	Public_ void run();
	Public_ void stop();
	Slot_ void addBehavior(VIGeneralBehavior*);
	Private_ void mergeEvent();
	Private_ void ergodicEvent();
	Private_ void eraseEvent();
};

