#pragma once
#include "VI2DGUIBase.h"

class VITextLabel : public VI2DGUILabel
{
	Q_OBJECT
public:
	VITextAnimation* Animation;
public:
	VITextLabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) :VI2DGUILabel(WidgetParent, AniParent) {
		this->setWordWrap(true);
		this->setObjectName("VIText");
		Animation = new VITextAnimation(this);
		BIND(Animation, SIGNAL(getText(QString)), this, SLOT(getText(QString)));
		BIND_DONE(Animation);
		Animation->setAnimationProcess(Process);
		this->setAlignment(Qt::AlignLeft);
		this->setGeometry(QRect(0, 0, 500, 60));
		this->show();
	}
public slots:
	void textNonlinerProgress(VIMath::VI2DMatrix mat) {
		Animation->enableNonlinearProgress(mat);
	}
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
	void setAlign(Qt::AlignmentFlag flag) {
		this->setAlignment(flag);
	}
};

class VIPictureLabel : public VI2DGUILabel
{
	Q_OBJECT
public:
	VIOpacityAnimation* OpacityAnimation;
	QImage Image;
public:
	VIPictureLabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) :VI2DGUILabel(WidgetParent, AniParent) {
		this->setObjectName("VIText");
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
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		if (!Image.isNull()) {
			QImage s = Image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			this->setPixmap(QPixmap::fromImage(s));
		}
		this->setGeometry(QRect(Parent->width() * px, Parent->height() * py, Parent->width() * pw, Parent->height() * ph));
		this->setStyleSheet("QLabel#VIText{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:30px;}");
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
	void setAlign(Qt::AlignmentFlag flag) {
		this->setAlignment(flag);
	}
};