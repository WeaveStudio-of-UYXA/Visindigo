#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "Visindigo/VICore/VIGuiAnimation.h"
class AEvent :public VIAnimationEvent 
{
	Q_OBJECT
signals:
	void move(float, float);
public:
	int max;
	AEvent INIT{
		this->setMaxMsec(500);
		max = 100;
	}
	void event() {
		emit move(max * (1 + qCos(3.14 * Percentage)), max * (1 + qCos(3.14 * Percentage)));
	}
};
class AWidget :public QWidget 
{
	Q_OBJECT
private:
	VIAnimationEventProcess* Process;
	QLabel* frameLabel;
	QLabel* TestLabel;
	QLabel* Test2Label;
	QPushButton* TestButton;
	QVBoxLayout* CurrentLayout;
	AEvent* Event;
	AEvent* Event2;
	QList<AEvent*> EventList;
public:
	AWidget(QWidget* parent = Q_NULLPTR) : QWidget(parent) {
		Process = new VIAnimationEventProcess(this);
		frameLabel = new QLabel(this);
		TestLabel = new QLabel(this);
		Test2Label = new QLabel(this);
		TestLabel->resize(30, 30);
		Test2Label->resize(30, 30);
		TestButton = new QPushButton(this);
		TestButton->setText("start");
		TestLabel->setStyleSheet("QLabel{background-color:#000000;}");
		Test2Label->setStyleSheet("QLabel{background-color:#000000;}");
		CurrentLayout = new QVBoxLayout(this);
		Event = new AEvent(this);
		Event2 = new AEvent(this);
		
		CurrentLayout->addWidget(frameLabel);
		CurrentLayout->addWidget(TestButton);
		connect(Process, SIGNAL(currentFrame(float)), this, SLOT(changeFrame(float)));
		Process->start();
		Event->setAnimationProcess(Process);
		Event2->setAnimationProcess(Process);
		BIND(Event, SIGNAL(move(float, float)), this, SLOT(moveB(float, float)));
		BIND(Event2, SIGNAL(move(float, float)), this, SLOT(moveB2(float, float)));
		connect(TestButton, SIGNAL(clicked()), this, SLOT(active()));
	}
public slots:
	void changeFrame(float frame) {
		frameLabel->setText(QString::number((int)frame));
	}
	void moveB(float x, float y) {
		this->TestLabel->move(x, y);
	}
	void moveB2(float x, float y) {
		this->Test2Label->move(200 - x, y);
	}
	void active() {
		Event->active();
		Event2->active();

			EventList.append(new AEvent(this));
			EventList.last()->setAnimationProcess(Process);
			EventList.last()->active();
		
	}
};
