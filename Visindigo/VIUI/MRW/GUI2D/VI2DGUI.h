#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "../../../../Visindigo/VICore/VIGuiAnimation.h"


class VITextAnimation : public VIAnimationEvent
{
	Q_OBJECT
signals:
	void getText(QString);
public:
	QString Text;
	QString Output;
	int MSPT;
	int MSW;
	int INDEX;
	float TEXTPERCENT;
	float LMS;
	QString::iterator Char;
	VITextAnimation INIT{
		MSPT = 300;
		MSW = 1500;
		INDEX = 0;
		LMS = 0;
	}
	void setText(QString text) {
		this->Text = text;
		this->setMaxMsec(Text.length() * MSPT + MSW);
		Char = Text.begin();
		Output = "";
	}
	void setSpeed(int MsPT) {
		this->MSPT = MsPT;
	}
	void setWait(int MsW) {
		this->MSW = MsW;
	}
	void event() {
		if (CurrentMsec >= LMS && Char != Text.end()) {
			Output += *Char;
			Char++;
			INDEX++;
			LMS = INDEX * MSPT;
			emit getText(Output);
		}
	}
};
class VITextLabel : private QLabel 
{
	Q_OBJECT
public:
	VITextAnimation* Animation;
public:
	VITextLabel(QWidget* WidgetParent,VIAnimationEventProcess* AniParent) {
		this->setParent(WidgetParent);
		this->QObject::setObjectName("VIText");
		Animation = new VITextAnimation(this);
		BIND(Animation, SIGNAL(getText(QString)), this, SLOT(getText(QString)));
		Animation->setAnimationProcess(AniParent);
	}
public slots:
	void setText(QString text, int mspt, int msw) {
		Animation->setSpeed(mspt);
		Animation->setWait(msw);
		Animation->setText(text);
		Animation->active();
	}
	void getText(QString text) {
		this->QLabel::setText(text);
	}
	void setStyleSheet(QString str) {
		this->QLabel::setStyleSheet(str);
	}
	void setGeometry(int X, int Y, int W, int H) {
		this->QLabel::setGeometry(X, Y, W, H);
	}

};