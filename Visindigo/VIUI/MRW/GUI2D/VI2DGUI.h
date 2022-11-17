#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "Visindigo/VICore/VIAnimation.h"
#include "VIJSAPI/VIJSGlobal.h"

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
	void continueTextAni(QString text, int mspt, int msw, bool wait) {
		Animation->setSpeed(mspt);
		Animation->setWait(msw);
		Animation->continueText(text);
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

class VIPictureLabel : public QLabel
{
	Q_OBJECT
public:
	VIOpacityAnimation* OpacityAnimation;
	VIAnimationEventProcess* Process;
	QImage Image;
	QWidget* Parent;
	bool Wait = false;
	bool SKIP = false;
	bool FINISH = false;
	QGraphicsOpacityEffect* Opacity;
	float px, py, pw, ph;
public:
	VIPictureLabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) {
		Process = AniParent;
		Parent = WidgetParent;
		px = 0.1; py = 0.4; pw = 0.8; ph = 0.2;
		this->setParent(WidgetParent);
		this->setObjectName("VIText");
		this->setWordWrap(true);
		Opacity = new QGraphicsOpacityEffect(this);
		this->setGraphicsEffect(Opacity);
		Opacity->setOpacity(1);
		OpacityAnimation = new VIOpacityAnimation(this);
		BIND(OpacityAnimation, SIGNAL(getOpacity(float)), this, SLOT(changeOpacity(float)));
		BIND(OpacityAnimation, SIGNAL(done(bool)), this, SLOT(ifWait(bool)));
		OpacityAnimation->setAnimationProcess(Process);
		connect(Parent, SIGNAL(mousePressed()), this, SLOT(skipOrJumpAni()));

		this->setAlignment(Qt::AlignCenter);
		this->setGeometry(QRect(0, 0, 500, 60));
		this->show();
	}
public slots:
	void setImage(QString path) {
		Image.load(path);
		QImage s = Image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		this->setPixmap(QPixmap::fromImage(s));
	}
	void resizeEvent(QResizeEvent* event) {
		QImage s = Image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		this->setPixmap(QPixmap::fromImage(s));
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
			Process->finishEvent(OpacityAnimation);
			FINISH = true;
		}
		else if (!SKIP && !FINISH) {
			Process->skipEvent(OpacityAnimation);
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