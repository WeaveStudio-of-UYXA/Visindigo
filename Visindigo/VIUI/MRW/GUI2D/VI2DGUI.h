#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "../../../../Visindigo/VICore/VIGuiAnimation.h"
#include "../../../../VIJSAPI/VIJSGlobal.h"

class VITextAnimation : public VIAnimationEvent
{
	Q_OBJECT
signals:
	void getText(QString);
public:
	QString Text;
	QString Output;
	int MSPT = 100;
	int MSW = 1500;
	int INDEX;
	float TEXTPERCENT;
	float LMS;
	bool SKIPED;
	QString::iterator Char;
	VITextAnimation INIT{
		INDEX = 0;
		LMS = 0;
		SKIPED = false;
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
		if (CurrentMsec >= LMS && Char != Text.end() && !SKIPED) {
			qDebug() << INDEX;
			Output += *Char;
			Char++;
			INDEX++;
			LMS = INDEX * MSPT;
			emit getText(Output);
		}
	}
	void skip() {
		qDebug() << Text;
		Char = Text.end();
		CurrentMsec = Text.length() * MSPT;
		emit getText(Text);
		SKIPED = true;
	}
};
class VITextLabel : public QLabel
{
	Q_OBJECT
public:
	VITextAnimation* Animation;
	VIAnimationEventProcess* Process;
	QWidget* Parent;
	bool Wait = false;
	bool SKIP = false;
	bool FINISH = false;
public:
	VITextLabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) {
		Process = AniParent;
		Parent = WidgetParent;
		this->setParent(WidgetParent);
		this->setObjectName("VIText");
		this->setWordWrap(true);
		Animation = new VITextAnimation(this);
		BIND(Animation, SIGNAL(getText(QString)), this, SLOT(getText(QString)));
		BIND(Animation, SIGNAL(done()), this, SLOT(ifWait()));
		Animation->setAnimationProcess(Process);
		connect(Parent, SIGNAL(mousePressed()), this, SLOT(skipOrJumpAni()));
		this->setStyleSheet("QLabel#VIText{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;}");
		this->setAlignment(Qt::AlignLeft);
		this->setGeometry(QRect(0, 0, 500, 60));
		this->show();
	}
public slots:
	void setTextAni(QString text, int mspt, int msw, bool wait) {
		Animation->setSpeed(mspt);
		Animation->setWait(msw);
		Animation->setText(text);
		SKIP = FINISH = false;
		Animation->active();
		Wait = wait;
	}
	void getText(QString text) {
		this->setText(text);
	}
	void skipOrJumpAni() {
		if (SKIP && !FINISH) {
			Process->finishEvent(Animation);
			FINISH = true;
		}
		else if (!SKIP && !FINISH) {
			Process->skipEvent(Animation);
			SKIP = true;
		}
	}
	void ifWait() {
		if (Wait) {
			VIJSHostWake;
		}
	}
};