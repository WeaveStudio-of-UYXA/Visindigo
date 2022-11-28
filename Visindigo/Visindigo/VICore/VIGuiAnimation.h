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
class VIAnimationEventProcess;

class VIAnimationEvent : public QObject
{
	Q_OBJECT
		friend class VIAnimationEventProcess;
signals:
	void done(bool);
	void midwaySignal(int, float);
	void addEventLater(VIAnimationEvent*);
public:
	float Percentage;
	float NonlinearPercentage;
	float MaxMsec;
	float CurrentMsec = 0;
	float NonlinearCurrentMsec = 0;
	QList<float> MidwaySignal;
	int MidwaySignalIndex = 0;
	VIAnimationEventProcess* Process = Q_NULLPTR;
	virtual void event() = 0;
	virtual void init() = 0;
	virtual void onFinish() {};
	VIMath::VI2DMatrix COEFF;
protected:
	bool ALIVE = false;
	bool SKIP = false;
	bool FINISH = false;
	bool DONE = false;
	bool NonlinearProgress = false;
public:
	VIAnimationEvent(QObject* parent = Q_NULLPTR) {
		this->setParent(parent);
	}
	void preInit() {
		Percentage = 0;
		CurrentMsec = 0;
		NonlinearCurrentMsec = 0;
		MidwaySignalIndex = 0;
		ALIVE = true;
		init();
	}
	void enableNonlinearProgress(VIMath::VI2DMatrix mat) {
		COEFF = VIBessel::getBesselCoefficient(mat);
		NonlinearProgress = true;
	}
	void disableNonlinearProgress() {
		NonlinearProgress = false;
	}
	void setMaxMsec(float msec) {
		this->MaxMsec = msec;
	}
	void setDoneSignal(bool sig) {
		this->DONE = sig;
	}
	float getProgress() {
		if (NonlinearProgress) {
			return NonlinearPercentage;
		}
		else {
			return Percentage;
		}
	}
	float getCurrentMsec() {
		if (NonlinearProgress) {
			return NonlinearCurrentMsec;
		}
		else {
			return CurrentMsec;
		}
	}
	void preDoEvent(float msTime) {
		if (ALIVE) {
			CurrentMsec += msTime;
			if (Percentage < 1) {
				Percentage = CurrentMsec / MaxMsec;
				if (NonlinearProgress) {
					NonlinearPercentage = VIBessel::getBesselValue(COEFF, Percentage).y;
					NonlinearCurrentMsec = NonlinearPercentage * MaxMsec;
				}
			}
			else { Percentage = 1; }
			this->event();
			if (MidwaySignalIndex<MidwaySignal.length() && getProgress() > MidwaySignal[MidwaySignalIndex]) {
				emit midwaySignal(MidwaySignalIndex, getProgress());
				MidwaySignalIndex++;
			}
			if (Percentage >= 1) {
				ALIVE = false;
				this->onFinish();
				NonlinearProgress = false;
				emit done(DONE);
			}
		}
	}
	void setMidwaySignal(QList<float>signalList) {
		MidwaySignal = signalList;
	}
public:
	void setAnimationProcess(VIAnimationEventProcess* process);
	virtual void skip() {};
	virtual void finish() {
		CurrentMsec = MaxMsec;
	}
public slots:
	void active();
};
class VIAnimationEventProcess : public QThread
{
	Q_OBJECT
signals:
	void currentFrame(float);
public:
	QMutex ProcessMutex;
private:
	QList<VIAnimationEvent*> EventQueue;
	QList<VIAnimationEvent*> EventDel;
	QList<VIAnimationEvent*> EventAdd;
	QList<VIAnimationEvent*> EventSkip;
	QList<VIAnimationEvent*> EventFinish;
	QMutex SleepMutex;
	QWaitCondition Condition;
	QWaitCondition WakeUp;
	float LASTTIME = 1;
	float Magnification = 1;
	QDateTime Time;
	bool RUN = true;
	bool WAIT = true;
	float FRAME = 0;
	short P30 = 300;
	int LFO5[5] = { 120, 120, 120, 120, 120 };
	short LFOINDEX = 0;
public:
	VIAnimationEventProcess(QObject* parent = Q_NULLPTR) : QThread(parent) {
		this->SleepMutex.lock();
	}
	void run() {
		while (true) {
			if (EventQueue.isEmpty()) {
				Condition.wait(&SleepMutex);
			}
			std::chrono::system_clock::time_point TPS = std::chrono::system_clock::now();
			this->ProcessMutex.lock();
			if (!EventAdd.isEmpty()) {
				for (auto i = EventAdd.begin(); i != EventAdd.end(); i++) {
					EventQueue.append(*i);
				}
				EventAdd.clear();
				WAIT = false;
			}
			if (!EventSkip.isEmpty()) {
				for (auto i = EventSkip.begin(); i != EventSkip.end(); i++) {
					(*i)->SKIP = true;
				}
				EventSkip.clear();
			}
			if (!EventFinish.isEmpty()) {
				for (auto i = EventFinish.begin(); i != EventFinish.end(); i++) {
					(*i)->FINISH = true;
				}
				EventFinish.clear();
			}
			this->ProcessMutex.unlock();
			for (auto i = EventQueue.begin(); i != EventQueue.end(); i++) {
				if ((*i)->ALIVE) {
					(*i)->preDoEvent(LASTTIME);
				}
				else {
					(*i)->SKIP = false;
					(*i)->FINISH = false;
					EventDel.append(*i);
				}
				if ((*i)->SKIP) {
					(*i)->skip();
					(*i)->SKIP = false;
				}
				else if ((*i)->FINISH) {
					(*i)->finish();
					(*i)->FINISH = false;
				}
			}
			if (!EventDel.isEmpty()) {
				for (auto i = EventDel.begin(); i != EventDel.end(); i++) {
					EventQueue.removeOne((*i));
				}
				EventDel.clear();
			}
			this->ProcessMutex.lock();
			if (EventQueue.isEmpty()) { WAIT = true; }
			if (!RUN) { break; }
			this->ProcessMutex.unlock();
			if (LASTTIME == 0) { LASTTIME = 0.001; }
			if (P30 < 1) {
				LFO5[LFOINDEX] = 1000 / LASTTIME;
				LFOINDEX += 1;
				emit currentFrame((LFO5[0] + LFO5[1] + LFO5[2] + LFO5[3] + LFO5[4]) / 5);
				if (LFOINDEX == 5) { LFOINDEX = 0; }
				P30 = 300;
			}
			else { P30--; }
			std::chrono::system_clock::time_point TPE = std::chrono::system_clock::now();
			LASTTIME = (float)(std::chrono::duration_cast<std::chrono::microseconds>(TPE.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::microseconds>(TPS.time_since_epoch()).count()) / 1000;
		}
	}
	void stop() {
		this->PROTECT;
		this->RUN = false;
		this->RELEASE;
	}
public slots:
	void addEvent(VIAnimationEvent* Event) {
		this->PROTECT;
		this->EventAdd.append(Event);
		if (WAIT) { Condition.wakeAll(); };
		this->RELEASE;
	}
	void skipEvent(VIAnimationEvent* Event) {
		this->PROTECT;
		this->EventSkip.append(Event);
		this->RELEASE;
	}
	void finishEvent(VIAnimationEvent* Event) {
		this->PROTECT;
		this->EventFinish.append(Event);
		this->RELEASE;
	}
};
