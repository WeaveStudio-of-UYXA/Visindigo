#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "VIGuiAnimation.h"
class AEvent :public VIAnimationEvent 
{
	Q_OBJECT
signals:
	void move(float, float);
public:
	int max;
	AEvent INIT{
		this->setMaxMsec(1000);
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
	QLabel* flameLabel;
	QLabel* TestLabel;
	QLabel* Test2Label;
	QPushButton* TestButton;
	QVBoxLayout* CurrentLayout;
	AEvent* Event;
public:
	AWidget(QWidget* parent = Q_NULLPTR) : QWidget(parent) {
		Process = new VIAnimationEventProcess(this);
		flameLabel = new QLabel(this);
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
		CurrentLayout->addWidget(flameLabel);
		CurrentLayout->addWidget(TestButton);
		connect(Process, SIGNAL(currentFlame(float)), this, SLOT(changeFlame(float)));
		Process->start();
		Event->setAnimationProcess(Process);
		BIND(Event, SIGNAL(move(float, float)), this, SLOT(moveB(float, float)));
		connect(TestButton, SIGNAL(clicked()), this, SLOT(active()));
	}
public slots:
	void changeFlame(float flame) {
		flameLabel->setText(QString::number(flame));
	}
	void moveB(float x, float y) {
		this->TestLabel->move(x, y);
		this->Test2Label->move(200 - x, y);
	}
	void active() {
		Event->init();
		Event->active();
	}
};
