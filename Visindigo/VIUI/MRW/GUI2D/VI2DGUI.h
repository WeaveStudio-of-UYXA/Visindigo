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
			Output += *Char;
			Char++;
			INDEX++;
			LMS = INDEX * MSPT;
			emit getText(Output);
		}
	}
	void skip() {
		Char = Text.end();
		CurrentMsec = Text.length() * MSPT;
		emit getText(Text);
		SKIPED = true;
	}
};

class VIOpacityAnimation :public VIAnimationEvent
{
	Q_OBJECT
signals:
	void getOpacity(float);
public:
	float OPBegin;
	float OPEnd;
	float OPDelta;
	VIOpacityAnimation INIT{

	}
	void setOpacity(float begin, float end, int ms, bool wait) {
		OPBegin = begin;
		OPEnd = end;
		OPDelta = qAbs(end - begin);
		this->setMaxMsec(ms);
		this->setDoneSignal(wait);
	}
	void event() {
		if (OPEnd > OPBegin) {
			float OP = OPBegin + Percentage * OPDelta;
			emit getOpacity(OP);
		}
		else {
			float OP = OPBegin - Percentage * OPDelta;
			emit getOpacity(OP);
		}
	}
	void skip() {
		emit getOpacity(OPEnd);
	}
	void finish() {
		emit getOpacity(OPEnd);
	}
};
class VITextLabel : public QLabel
{
	Q_OBJECT
public:
	VITextAnimation* Animation;
	VIOpacityAnimation* OpacityAnimation;
	VIAnimationEventProcess* Process;
	QWidget* Parent;
	bool Wait = false;
	bool SKIP = false;
	bool FINISH = false;
	QGraphicsOpacityEffect* Opacity;
	float px, py, pw, ph;
public:
	VITextLabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) {
		Process = AniParent;
		Parent = WidgetParent;
		px = 0.1; py = 0.4; pw = 0.8; ph = 0.2;
		this->setParent(WidgetParent);
		this->setObjectName("VIText");
		this->setWordWrap(true);
		Opacity = new QGraphicsOpacityEffect(this);
		this->setGraphicsEffect(Opacity);
		Opacity->setOpacity(1);
		Animation = new VITextAnimation(this);
		OpacityAnimation = new VIOpacityAnimation(this);
		BIND(Animation, SIGNAL(getText(QString)), this, SLOT(getText(QString)));
		BIND(OpacityAnimation, SIGNAL(getOpacity(float)), this, SLOT(changeOpacity(float)));
		BIND(Animation, SIGNAL(done(bool)), this, SLOT(ifWait(bool)));
		BIND(OpacityAnimation, SIGNAL(done(bool)), this, SLOT(ifWait(bool)));
		Animation->setAnimationProcess(Process);
		OpacityAnimation->setAnimationProcess(Process);
		connect(Parent, SIGNAL(mousePressed()), this, SLOT(skipOrJumpAni()));
		
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
		Animation->setDoneSignal(wait);
		Animation->active();
	}
	void getText(QString text) {
		this->setText(text);
	}
	void setOpacityAni(float start, float end, int ms, bool wait) {
		OpacityAnimation->setOpacity(start, end, ms, wait);
		OpacityAnimation->active();
	}
	void changeOpacity(float op) {
		this->Opacity->setOpacity(op);
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
	void ifWait(bool Wait) {
		if (Wait) {
			VIJSHostWake;
		}
	}
	void setAlign(Qt::AlignmentFlag flag) {
		this->setAlignment(flag);
	}
	void setGeometryPercent(float px, float py, float pw, float ph) {
		this->px = px;
		this->py = py;
		this->pw = pw;
		this->ph = ph;
		this->resizeEvent();
	}
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		this->setGeometry(QRect(Parent->width() * px, Parent->height() * py, Parent->width() * pw, Parent->height() * ph));
		this->setStyleSheet("QLabel#VIText{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:30px;}");
	}
};