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
	void preDoEvent(float msTime) {
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
	void currentFrame(float);
private:
	QList<VIAnimationEvent*> EventQueue;
	QMutex ProcessMutex;
	QMutex SleepMutex;
	QWaitCondition Condition;
	float LASTTIME = 1;
	QDateTime Time;
	bool RUN = true;
	bool WAIT = true;
	int START = 0;
	int END = 0;
	float FRAME = 0;
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
				//START = QDateTime::currentMSecsSinceEpoch();
				std::chrono::system_clock::time_point TPS = std::chrono::system_clock::now();
				for (auto i = EventQueue.begin(); i != EventQueue.end(); i++) {
					(*i)->preDoEvent(LASTTIME);
				}
				if (LASTTIME == 0) { LASTTIME = 0.001; }
				if (P30 < 1) {
					FRAME = 1000 / LASTTIME;
					emit currentFrame(FRAME);
					P30 = 3000;
				}
				else { P30--; }
				//END = QDateTime::currentMSecsSinceEpoch();
				std::chrono::system_clock::time_point TPE = std::chrono::system_clock::now();
				LASTTIME = (float)(std::chrono::duration_cast<std::chrono::microseconds>(TPE.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::microseconds>(TPS.time_since_epoch()).count()) / 1000;
				//qDebug() << LASTTIME;
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
