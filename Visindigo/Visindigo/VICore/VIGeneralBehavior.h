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
#include "../../CommonEdit/CECore/CEMacro.h"
#include "macro/VIGeneralBehavior_m.h"


class VIDuration :public QObject
{
	Q_OBJECT;
	Public ENUM Unit {
		NanoSecond,
		MilliSecond,
		Second,
	};
	Public ENUM PercentType {
		Linear, 
		Nonlinear,
	};
	Signal void timeout();
	Private VIMilliSecond MSEC = 0;
	Private VIMilliSecond CURRENT;
	Private float PERCENT;
	Private float PERCENT_NL;
	Private VIMath::VI2DMatrix COEFF;
	Private bool TIMEOUTFLAG = false;
	Public VIDuration(QObject* parent = Q_NULLPTR) : QObject(parent) {};
	Public void init();
	Public void setDuration(VIMilliSecond);
	Public double getDuration(Unit);
	Public float getPercent(PercentType);
	Public void setBesselCoeff(VIMath::VI2DMatrix);
	Public bool isTimeout();
	Slot void addTime(unsigned long long, Unit);
};



class VIGeneralBehavior :public QObject
{
	Q_OBJECT;
	friend class VIGeneralBehaviorHost;
	Public ENUM State {
		Idle,
		Active,
		Skip,
		Done,
	};
	Protected VIGeneralBehaviorHost* HOST = nullptr;
	Protected VIDuration* DURATION = nullptr;
	Protected State STATE = State::Idle;
	Signal void addBehaviorLater(VIGeneralBehavior*);
	Signal void done();
	Private void preFrame(VINanoSecond);
	Protected void setHost(VIGeneralBehaviorHost*);
	Protected void setDuration(VIMilliSecond);
	Protected VIMilliSecond getDuration();
	Protected float getPercent(VIDuration::PercentType);
	Protected void setBesselCoeff(VIMath::VI2DMatrix);
	Public VIGeneralBehavior(QObject* parent = Q_NULLPTR) :QObject(parent) {
		this->DURATION = new VIDuration(this);
	}
	Public virtual void onActive() = 0;
	Public virtual void onFrame() = 0;
	Public virtual void onSkip() {};
	Public virtual void onDone() {};
	Public State getBehaviorState();
	Slot void active();
};

class VIGeneralBehaviorHost :public QObject {
	
};