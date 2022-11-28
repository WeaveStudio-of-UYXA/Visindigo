#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "Visindigo/VICore/VIAnimation.h"
#include "Visindigo/VICore/VIQtExtensionMethod.h"
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
	bool wToh = false;
	QString StyleSheets;
	VI2DGUILabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) {
		Parent = WidgetParent;
		Process = AniParent;
		this->setParent(Parent);
		Opacity = new QGraphicsOpacityEffect(this);
		OpacityAnimation = new VIOpacityAnimation(this);
		this->setGraphicsEffect(Opacity);
		Opacity->setOpacity(1);
		BIND(OpacityAnimation, SIGNAL(getOpacity(float)), this, SLOT(setOpacity(float)));
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
	void setOpacity(float op) {
		this->Opacity->setOpacity(op);
	}
	void setGeometryPercent(float px, float py, float pw, float ph) {
		this->px = px;
		this->py = py;
		this->pw = pw;
		this->ph = ph;
		this->resizeEvent();
		this->wToh = false;
	}
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		if (wToh) {
			this->setGeometry(Parent->width() * px, Parent->height() * py, Parent->width() * pw, Parent->width() * ph);
		}
		else {
			this->setGeometry(Parent->width() * px, Parent->height() * py, Parent->width() * pw, Parent->height() * ph);
		}
		QLabel::setStyleSheet(VIQtExtMethod::QSSExtensionAUTOPR(StyleSheets, this));
	}
	void setStyleSheet(QString StyleSheet) {
		this->StyleSheets = StyleSheet;
		QLabel::setStyleSheet(VIQtExtMethod::QSSExtensionAUTOPR(StyleSheets, this));
	}
	void setAlignment(Qt::AlignmentFlag Align) {
		QLabel::setAlignment(Align);
	}
	void movePercent(float px, float py) {
		this->px = px;
		this->py = py;
		this->move(Parent->width() * px, Parent->height() * py);
	}
	void resizePercent(float pw, float ph) {
		this->pw = pw;
		this->ph = ph;
		this->resize(Parent->width() * pw, Parent->height() * ph);
		this->wToh = false;
	}
	void resizeWidthAndRatio(float pw, float pwtoph) {
		this->pw = pw;
		this->ph = pw * pwtoph;
		this->resize(Parent->width() * pw, Parent->width() * ph);
		this->wToh = true;
	}
};