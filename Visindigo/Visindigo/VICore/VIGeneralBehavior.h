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
	pPublic ENUM Unit{
		NanoSecond,
		MilliSecond,
		Second,
	};
	pPublic ENUM PercentType{
		Linear,
		Nonlinear,
	};
	pSignal void timeout();
	pPrivate VIMilliSecond MSEC = 0;
	pPrivate double CURRENT;
	pPrivate float PERCENT;
	pPrivate float PERCENT_NL;
	pPrivate VIMath::VI2DMatrix COEFF;
	pPrivate bool TIMEOUTFLAG = false;
	pPublic VIDuration(QObject* parent = Q_NULLPTR) : QObject(parent) {};
	pPublic void init();
	pPublic void setDuration(VIMilliSecond);
	pPublic double getDuration(Unit);
	pPublic float getPercent(PercentType);
	pPublic double getCurrent();
	pPublic void setBesselCoeff(VIMath::VI2DMatrix);
	pPublic bool isTimeout();
	pSlot void addTime(unsigned long long, Unit);
};

class VIGeneralBehavior :public QObject
{
	Q_OBJECT;
	friend class VIGeneralBehaviorHost;
	pPublic ENUM State{
		Idle,
		Active,
		Skip,
		Done,
	};
	pProtected VIGeneralBehaviorHost* HOST = nullptr;
	pProtected VIDuration* DURATION = nullptr;
	pProtected QMutex RESMUTEX;
	pPrivate State STATE = State::Idle;
	pSignal void addBehaviorLater(VIGeneralBehavior*);
	pSignal void done();
	pProtected void preFrame(VINanoSecond);
	pPublic void setHost(VIGeneralBehaviorHost*);
	pProtected void setDuration(VIMilliSecond);
	pProtected VIMilliSecond getDuration();
	pProtected float getPercent(VIDuration::PercentType);
	pProtected double getCurrent();
	pProtected void setBesselCoeff(VIMath::VI2DMatrix);
	pPublic VIGeneralBehavior(QObject* parent = Q_NULLPTR) :QObject(parent) {
		this->DURATION = new VIDuration(this);
	}
	pProtected virtual void onActive() = 0;
	pProtected virtual void onFrame() = 0;
	pProtected virtual void onSkip() {};
	pProtected virtual void onDone() {};
	pPublic void setBehaviorState(State);
	pPublic State getBehaviorState();
	pSlot void active();
};


class VIGeneralBehaviorHost :public QThread {
	Q_OBJECT;
	friend class VIGeneralBehavior;
	pPublic static VIGeneralBehaviorHost* VIGeneralBehaviorHostInstance;
	pPrivate QVector<VIGeneralBehavior*> BEHAVIORLIST;
	pPrivate QVector<VIGeneralBehavior*> BEHAVIORLIST_ADD;
	pProtected static QMutex HOSTMUTEX;
	pProtected static QMutex SLEEPMUTEX;
	pProtected static QWaitCondition SLEEPWAIT;
	pPrivate bool HOSTFLAG = false;
	pPrivate bool SLEEPFLAG = false;
	pPrivate VINanoSecond LASTTIME = 10;
	pPublic def_init VIGeneralBehaviorHost(QObject* parent = Q_NULLPTR) :QThread(parent) { SLEEPMUTEX.lock(); }
	pPrivate void setHostFlag(bool);
	pPrivate bool getHostFlag();
	pPrivate void setSleep(bool);
	pPublic bool isSleep();
	pPublic void run();
	pPublic void stop();
	pSlot void addBehavior(VIGeneralBehavior*);
	pPrivate void mergeEvent();
	pPrivate void ergodicEvent();
	pPrivate void eraseEvent();
};

