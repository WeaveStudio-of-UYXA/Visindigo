#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "Visindigo/VICore/VIAnimation.h"
#include "Visindigo/VICore/VIGeneralBehavior.h"
#include "Visindigo/VICore/VIQtExtensionMethod.h"
#include "VIJSAPI/VIJSGlobal.h"
#define BIND_DONE(VIAniEvent) BIND(VIAniEvent, SIGNAL(done(bool)), this, SLOT(ifWait(bool)));
class VI2DGUILabel :public QLabel
{
	Q_OBJECT
signals:
	void removeThis(VI2DGUILabel*);
public:
	QWidget* Parent;
	bool Wait = false;
	bool SKIP = false;
	bool FINISH = false;
	QGraphicsOpacityEffect* Opacity;
	VIOpacityAniBehavior* OpacityAniBehavior;
	float px, py, pw, ph;
	float pCx, pCy;
	bool wToh = false;
	bool mC = false;
	QString StyleSheets;
	VI2DGUILabel(QWidget* WidgetParent) {
		Parent = WidgetParent;
		this->setParent(Parent);
		connect(this, SIGNAL(removeThis(VI2DGUILabel*)), Parent, SLOT(removeVI2DGUILabel(VI2DGUILabel*)));
		Opacity = new QGraphicsOpacityEffect(this);
		this->setGraphicsEffect(Opacity);
		Opacity->setOpacity(1);
		OpacityAniBehavior = new VIOpacityAniBehavior(this);
		BIND(OpacityAniBehavior, SIGNAL(getOpacity(float)), this, SLOT(setOpacity(float)));
		BIND(OpacityAniBehavior, SIGNAL(done()), this, SLOT(getDone()));
		OpacityAniBehavior->setHost(gBEHAVIOR);
		connect(Parent, SIGNAL(mousePressed()), this, SLOT(skipOrJumpAni()));
		px = 0.1; py = 0.2; pw = 0.8; ph = 0.6;
	}
	~VI2DGUILabel() {
		qDebug() << "deleted";
		emit removeThis(this);
		this->disconnect();
	}
public slots:
	void del() {
		this->deleteLater();
	}
	virtual void skipOrJumpAni() {}
	void getDone() {
		VIGuiAnimation* Sender = dynamic_cast<VIGuiAnimation*>(this->sender());
		if (Sender->ifWait()) { VIJSHostWake; }
	}
	void setOpacityAni(float start, float end, int ms, bool wait) {
		OpacityAniBehavior->setOpacity(start, end, ms);
		OpacityAniBehavior->setWait(wait);
		OpacityAniBehavior->active();
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
			this->resize(Parent->width() * pw, Parent->width() * ph);
		}
		else {
			this->resize(Parent->width() * pw, Parent->height() * ph);
		}
		if (mC) {
			this->move(Parent->width() * pCx - this->width() / 2, Parent->height() * pCy - this->height() / 2);
		}
		else {
			this->move(Parent->width() * px, Parent->height() * py);
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
		this->mC = false;
	}
	void resizePercent(float pw, float ph) {
		this->pw = pw;
		this->ph = ph;
		this->resize(Parent->width() * pw, Parent->height() * ph);
		this->wToh = false;
		this->mC = false;
	}
	void resizeWidthAndRatio(float pw, float pwtoph) {
		this->pw = pw;
		this->ph = pw * pwtoph;
		this->resize(Parent->width() * pw, Parent->width() * ph);
		this->wToh = true;
	}
	void moveCenter(float pCx, float pCy) {
		this->move(Parent->width() * pCx - this->width() / 2, Parent->height() * pCy - this->height() / 2);
		this->mC = true;
	}
};