#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "Visindigo/VICore/VIAnimation.h"
#include "VIJSAPI/VIJSGlobal.h"
#define BIND_DONE(VIAniEvent) BIND(VIAniEvent, SIGNAL(done(bool)), this, SLOT(ifWait(bool)));
class VI2DGUILabel :public QLabel
{
	Q_OBJECT
public:
	QWidget* Parent;
	VIAnimationEventProcess* Process;
	bool Wait = false;
	bool SKIP = false;
	bool FINISH = false;
	QGraphicsOpacityEffect* Opacity;
	VIOpacityAnimation* OpacityAnimation;
	float px, py, pw, ph;
	QString StyleSheets;
	VI2DGUILabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) {
		Parent = WidgetParent;
		Process = AniParent;
		this->setParent(Parent);
		Opacity = new QGraphicsOpacityEffect(this);
		OpacityAnimation = new VIOpacityAnimation(this);
		this->setGraphicsEffect(Opacity);
		Opacity->setOpacity(1);
		BIND(OpacityAnimation, SIGNAL(getOpacity(float)), this, SLOT(changeOpacity(float)));
		BIND_DONE(OpacityAnimation);
		OpacityAnimation->setAnimationProcess(Process);
		connect(Parent, SIGNAL(mousePressed()), this, SLOT(skipOrJumpAni()));
		px = 0.1; py = 0.2; pw = 0.8; ph = 0.6;
	}
public slots:
	virtual void skipOrJumpAni() {}
	void ifWait(bool Wait) {
		if (Wait) {
			VIJSHostWake;
		}
	}
	void setOpacityAni(float start, float end, int ms, bool wait) {
		OpacityAnimation->setOpacity(start, end, ms, wait);
		OpacityAnimation->active();
	}
	void changeOpacity(float op) {
		this->Opacity->setOpacity(op);
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