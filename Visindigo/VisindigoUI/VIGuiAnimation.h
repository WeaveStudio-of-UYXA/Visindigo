#pragma once
#include<QtCore>
#define INIT (QWidget* parent = Q_NULLPTR) :VIAnimationEvent(parent) {} void init() 
#define BIND(objP1,signal,objP2,slot) connect(objP1,signal,objP2,slot,Qt::BlockingQueuedConnection)
class VIAnimationEventProcess;

class VIAnimationEvent : public QObject
{
	Q_OBJECT
signals:
	void destroyLater(VIAnimationEvent* p);
public:
	float Percentage;
	float MaxMsec;
	float CurrentMsec = 0;
	VIAnimationEventProcess* Process;
	virtual void event() = 0;
	virtual void init() = 0;
	void connectProcess();
	void disconnectProcess();
	bool ALIVE = false;
	VIAnimationEvent(QObject* parent = Q_NULLPTR) {
		this->setParent(parent);
	}
	void preInit() {
		Percentage = 0;
		CurrentMsec = 0;
		connectProcess();
		ALIVE = true;
		init();
	}
	void setMaxMsec(float msec) {
		this->MaxMsec = msec;
	}
	void preDoEvent(int msTime) {
		if (ALIVE) {
			CurrentMsec += msTime;
			if (Percentage < 1) {
				Percentage = CurrentMsec / MaxMsec;
			}
			else { Percentage = 1; }
			this->event();
			if (Percentage >= 1) {
				emit destroyLater(this);
				disconnectProcess();
				ALIVE = false;
			}
		}
	}
public:
	void setAnimationProcess(VIAnimationEventProcess* process) {
		this->Process = process;
	}
public slots:
	void active();
};
class VIAnimationEventProcess : public QThread
{
	Q_OBJECT
signals:
	void currentFlame(float);
private:
	QList<VIAnimationEvent*> EventQueue;
	QMutex ProcessMutex;
	QMutex SleepMutex;
	QWaitCondition Condition;
	int LASTTIME = 1;
	QDateTime Time;
	bool RUN = true;
	bool WAIT = true;
	int START = 0;
	int END = 0;
	float FLAME = 0;
	int P30 = 300;
public:
	VIAnimationEventProcess(QObject* parent = Q_NULLPTR) : QThread(parent) {
		this->SleepMutex.lock();
	}
	void run() {
		while (RUN) {
			this->ProcessMutex.lock();
			if (this->EventQueue.isEmpty()) {
				this->ProcessMutex.unlock();
				Condition.wait(&SleepMutex);
			}
			else {
				START = QDateTime::currentMSecsSinceEpoch();
				for (auto i = EventQueue.begin(); i != EventQueue.end(); i++) {
					(*i)->preDoEvent(LASTTIME);
				}
				if (LASTTIME == 0) { LASTTIME = 1; }
				if (P30 < 1) {
					FLAME = 1000 / LASTTIME;
					emit currentFlame(FLAME);
					P30 = 300;
				}
				else { P30--; }
				//if (5 - LASTTIME > 0) { this->sleep(5 - LASTTIME); }
				END = QDateTime::currentMSecsSinceEpoch();
				LASTTIME = END - START;
				this->ProcessMutex.unlock();
			}
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
		if (this->EventQueue.isEmpty()) { Condition.wakeAll(); }
		this->EventQueue.append(Event);
		this->ProcessMutex.unlock();
	}
	void removeEvent(VIAnimationEvent* Event) {
		this->ProcessMutex.lock();
		this->EventQueue.removeOne(Event);
		this->ProcessMutex.unlock();
	}
};
