﻿#pragma once
#include "VI2DGUIBase.h"

class VITextLabel : public VI2DGUILabel
{
	Q_OBJECT
public:
	VITextAniBehavior* Behavior;
	bool wait;
public:
	VITextLabel();
	VITextLabel(QWidget* WidgetParent) :VI2DGUILabel(WidgetParent) {
		this->setWordWrap(true);
		//this->setObjectName("VIText");
		Behavior = new VITextAniBehavior(this);
		BIND(Behavior, SIGNAL(getText(QString)), this, SLOT(getText(QString)));
		BIND(Behavior, SIGNAL(done()), this, SLOT(ifHostWait()));
		Behavior->setHost(gBEHAVIOR);
		this->setAlignment(Qt::AlignLeft);
		this->setGeometry(QRect(0, 0, 500, 60));
	}
public slots:
	void setBesselPoints(VIMath::VI2DMatrix Pmat) {
		Behavior->setBesselCoeff(VIBessel::getBesselCoefficient(Pmat));
		qDebug() << "setB";
	}
	void setText(QString text) {
		QLabel::setText(text);
	}
	void setTextAni(QString text, int mspt, int msw, bool wait) {
		Behavior->setTextAni(text, mspt, msw, false);
		SKIP = FINISH = false;
		this->wait = wait;
		Behavior->active();
	}
	void continueTextAni(QString text, int mspt, int msw, bool wait) {
		Behavior->setTextAni(text, mspt, msw, true);
		SKIP = FINISH = false;
		this->wait = wait;
		Behavior->active();
	}
	void getText(QString text) {
		QLabel::setText(text);
	}
	void skipOrJumpAni() {
		if (SKIP && !FINISH) {
			Behavior->setBehaviorState(VIGeneralBehavior::State::Done);
			FINISH = true;
		}
		else if (!SKIP && !FINISH) {
			Behavior->setBehaviorState(VIGeneralBehavior::State::Skip);
			SKIP = true;
		}
	}
	void ifHostWait() {
		if (wait) {
			VIJSHostWake;
		}
	}
};

class VIPictureLabel : public VI2DGUILabel
{
	Q_OBJECT
public:
	QImage Image;
public:
	VIPictureLabel(QWidget* WidgetParent) :VI2DGUILabel(WidgetParent) {
		this->setAlignment(Qt::AlignCenter);
		this->setGeometry(QRect(0, 0, 500, 60));
	}
public slots:
	void setImage(QString path) {
		Image.load(path);
		QImage s = Image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		this->setPixmap(QPixmap::fromImage(s));
	}
	void fillColor(int r, int g, int b, int a) {
		Image = QImage(this->width(), this->height(), QImage::Format_ARGB32);
		Image.fill(QColor(r, g, b, a));
		this->setPixmap(QPixmap::fromImage(Image));
	}
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		VI2DGUILabel::resizeEvent(event);
		if (!Image.isNull()) {
			QImage s = Image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			this->setPixmap(QPixmap::fromImage(s));
		}
	}
	void releaseMemory() {
		Image = QImage();
		this->clear();
	}
	void skipOrJumpAni() {
		if (SKIP && !FINISH) {
			OpacityAniBehavior->setBehaviorState(VIGeneralBehavior::State::Done);
			FINISH = true;
		}
		else if (!SKIP && !FINISH) {
			OpacityAniBehavior->setBehaviorState(VIGeneralBehavior::State::Skip);
			SKIP = true;
		}
	}
	void setAlign(Qt::AlignmentFlag flag) {
		this->setAlignment(flag);
	}
};