/*
此文件用于实现Visindigo2D的总动画效果
实际上对于Qt的2D动画，只需要使用QPropertyAnimation即可
或者选择使用QPropertyAnimation的子类QVariantAnimation
此文档的意义在于针对Visindigo本身的需求提供一个在动画上相对通用的队列处理系统
*/
#pragma once
#include<QtCore>
#include<QtWidgets>
#include <chrono>
#include "VIMath.h"
#define INIT (QWidget* parent = Q_NULLPTR) :VIAnimationEvent(parent) {} void init()
#define BIND(objP1,signal,objP2,slot) connect(objP1,signal,objP2,slot,Qt::BlockingQueuedConnection)
#define PROTECT ProcessMutex.lock();
#define RELEASE ProcessMutex.unlock();
#define EVENT void event()
typedef unsigned long long VIMilliSecond;
typedef unsigned long long VINanoSecond;
typedef unsigned long long VISecond;
class VIDuration :public QObject
{
	Q_OBJECT
public:
	enum class Unit {
		NanoSecond,
		MilliSecond,
		Second,
	};
	enum class PercentType {
		Linear, 
		Nonlinear,
	};
signals:
	void timeout();
private:
	VIMilliSecond MSEC = 0;
	VIMilliSecond CURRENT = 0;
	float PERCENT = 0;
	float PERCENT_NL = 0;
	VIMath::VI2DMatrix COEFF = { {0, 0}, {1, 1} };
	bool TIMEOUTFLAG = false;
public:
	VIDuration(VIMilliSecond);
public:
	void init();
	void setDuration(VIMilliSecond);
	double getDuration(Unit);
	float getPercent(PercentType);
	void setBesselCoeff(VIMath::VI2DMatrix);
public slots:
	void addTime(unsigned int, Unit);
};

class VIGeneralBehaviorHost;

class VIGeneralBehavior :public QObject
{
	Q_OBJECT
private:
	enum class State {
		Idle,
		Active,
		Skip,
		Finish,
	};
private:
	VIGeneralBehaviorHost* HOST = nullptr;
	VIDuration* DURATION = nullptr;
protected:
	State STATE = State::Idle;
signals:
	void done();
private:
	void preInit(){};
	void preFrame() {};
protected:
	void setHost(VIGeneralBehaviorHost*);
public:
	VIGeneralBehavior(QObject*) {};
	virtual void init() = 0;
	virtual void onActive() = 0;
	virtual void frame() = 0;
	virtual void onSkip() {};
	virtual void onDone() {};
public slots:
	void active() {};
};

