#pragma once
#include<QtCore>
#include <chrono>
#define INIT (QWidget* parent = Q_NULLPTR) :VIAnimationEvent(parent) {} void init() 
#define BIND(objP1,signal,objP2,slot) connect(objP1,signal,objP2,slot,Qt::BlockingQueuedConnection)
class VIAnimationEventProcess;

class VIAnimationEvent : public QObject
{
	Q_OBJECT
signals:
	void destroyLater(VIAnimationEvent* p);
	void addEventLater(VIAnimationEvent* p);
public:
	float Percentage;
	float MaxMsec;
	float CurrentMsec = 0;
	VIAnimationEventProcess* Process = Q_NULLPTR;
	virtual void event() = 0;
	virtual void init() = 0;
	bool ALIVE = false;
	VIAnimationEvent(QObject* parent = Q_NULLPTR) {
		this->setParent(parent);
	}
	void preInit() {
		Percentage = 0;
		CurrentMsec = 0;
		ALIVE = true;
		init();
	}
	void setMaxMsec(float msec) {
		this->MaxMsec = msec;
	}
	void preDoEvent(float msTime) {
		if (ALIVE) {
			CurrentMsec += msTime;
			
			if (Percentage < 1) {
				Percentage = CurrentMsec / MaxMsec;
			}
			else { Percentage = 1; }
			this->event();
			if (Percentage >= 1) {
				ALIVE = false;
			}
		}
	}
public:
	void setAnimationProcess(VIAnimationEventProcess* process);
public slots:
	void active();
};
class VIAnimationEventProcess : public QThread
{
	Q_OBJECT
signals:
	void currentFrame(float);
private:
	QList<VIAnimationEvent*> EventQueue;
	QList<VIAnimationEvent*> EventDel;
	QList<VIAnimationEvent*> EventAdd;
	QMutex ProcessMutex;
	QMutex SleepMutex;
	QWaitCondition Condition;
	QWaitCondition WakeUp;
	float LASTTIME = 1;
	QDateTime Time;
	bool RUN = true;
	bool WAIT = true;
	float FRAME = 0;
	short P30 = 300;
	short LFO5[5] = { 120, 120, 120, 120, 120 };
	short LFOINDEX = 0;
public:
	VIAnimationEventProcess(QObject* parent = Q_NULLPTR) : QThread(parent) {
		this->SleepMutex.lock();
	}
	void run() {
		while (RUN) {
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
			this->ProcessMutex.unlock();
			for (auto i = EventQueue.begin(); i != EventQueue.end(); i++) {
				if ((*i)->ALIVE) {
					(*i)->preDoEvent(LASTTIME);
				}
				else {
					EventDel.append((*i));
				}
			}
			for (auto i = EventDel.begin(); i != EventDel.end(); i++) {
				EventQueue.removeOne((*i));
			}
			if (!EventDel.isEmpty()) { EventDel.clear(); }
			this->ProcessMutex.lock();
			if (EventQueue.isEmpty()) {WAIT = true;}
			this->ProcessMutex.unlock();
			if (LASTTIME == 0) { LASTTIME = 0.001; }
			if (P30 < 1) {
				LFO5[LFOINDEX] = 1000 / LASTTIME;
				LFOINDEX += 1;
				emit currentFrame((LFO5[0]+ LFO5[1] + LFO5[2] + LFO5[3] + LFO5[4])/5);
				if (LFOINDEX == 5) { LFOINDEX = 0; }
				P30 = 300;
			}
			
			else { P30--; }
			std::chrono::system_clock::time_point TPE = std::chrono::system_clock::now();
			LASTTIME = (float)(std::chrono::duration_cast<std::chrono::microseconds>(TPE.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::microseconds>(TPS.time_since_epoch()).count()) / 1000;			
		}
	}
	void stop() {
		this->ProcessMutex.lock();
		this->RUN = false;
		this->ProcessMutex.unlock();
	}
public slots:
	void addEvent(VIAnimationEvent* Event) {
		this->ProcessMutex.lock();
		this->EventAdd.append(Event);
		if (WAIT) { Condition.wakeAll(); };
		this->ProcessMutex.unlock();	
	}
};
