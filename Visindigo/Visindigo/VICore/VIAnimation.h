#pragma once
#include "VIGuiAnimation.h"
#include "VIGeneralBehavior.h"
#include "VIMainBehavior.h"

class VIGuiAnimation :public VIMainBehavior
{
	Q_OBJECT;
	_Private bool WAITFLAG;
	_Private QLabel* LABEL;
	_Public def_init VIGuiAnimation(QObject* parent = Q_NULLPTR) :VIMainBehavior(parent) {}
	_Public bool ifWait() {
		return this->WAITFLAG;
	};
	_Public void setWait(bool w) {
		this->WAITFLAG = w;
	}
};

class VITextAniBehavior :public VIGuiAnimation
{
	Q_OBJECT;
	_Public def_init VITextAniBehavior(QObject* parent = Q_NULLPTR) :VIGuiAnimation(parent) {}
	_Signal void getText(QString);
	_Private QString BEFORE = "";
	_Private QString TEXT = "";
	_Private QString CURRENT = "";
	_Private QString::iterator CHAR;
	_Private VIMilliSecond LMS;
	_Private VIMilliSecond MSPT;
	_Private VIMilliSecond MSW;
	_Private int INDEX;
	_Slot void setTextAni(QString text, int MsPT, int MsW, bool continueAni) {
		BEFORE = TEXT;
		TEXT = text;
		if (!continueAni) { CURRENT = ""; BEFORE = ""; }
		else { CURRENT = BEFORE; }
		MSPT = MsPT;
		MSW = MsW;
		this->setDuration(text.length() * MsPT + MsW);
	}
	_Protected void onActive() {
		LMS = 0;
		INDEX = 0;
		CHAR = TEXT.begin();
	}
	_Protected void onFrame() {
		getLastTime();
		if (getCurrent() >= LMS && CHAR != TEXT.end() && getBehaviorState()!=State::Skip) {
			CURRENT += *CHAR;
			CHAR++;
			INDEX++;
			LMS = INDEX * MSPT;
			emit getText(CURRENT);
		}
		//qDebug() << "Percent" << this->getPercent(VIDuration::PercentType::Linear) << "Duration" << this->getDuration();
	}
	_Protected void onSkip() {
		CHAR = TEXT.end();
		//this->setDuration(TEXT.length() * MSPT);
		emit getText(BEFORE + TEXT);
	}
	_Protected void onDone() {
		emit getText(BEFORE + TEXT);
	}
};

class VIOpacityAniBehavior :public VIGuiAnimation
{
	Q_OBJECT;
	_Public float OPBegin;
	_Public float OPEnd;
	_Public float OPDelta;
	_Public VIMilliSecond JUMPTIME;
	_Public QGraphicsOpacityEffect* OPEffect;
	_Public def_init VIOpacityAniBehavior(QObject* parent = Q_NULLPTR):VIGuiAnimation(parent) {}
	_Public void setOpacity(float begin, float end, int ms) {
		OPBegin = begin;
		OPEnd = end;
		OPDelta = end - begin;
		this->setDuration(ms);
	}
	_Slot void onActive() {
		JUMPTIME = 0;
	}
	_Slot void onFrame() {
		float OP = OPBegin + this->getPercent(VIDuration::PercentType::Linear) * OPDelta;
		OPEffect->setOpacity(OP);
	}
	_Slot void onDone() {
		OPEffect->setOpacity(OPEnd);
	}
	_Slot void onSkip() {
		OPEffect->setOpacity(OPEnd);
	}
};

class VIResizeAniBehavior :public VIGuiAnimation
{
	Q_OBJECT;
	_Signal void getSize(QSize);
	_Public QSize SizeBegin;
	_Public QSize SizeEnd;
	_Public QSize SizeDelta;
	_Public VIMilliSecond JUMPTIME;
	_Public def_init VIResizeAniBehavior(QObject* parent = Q_NULLPTR) :VIGuiAnimation(parent) {}
	_Public void setSize(QSize& SizeBegin, QSize& SizeEnd, VIMilliSecond duration) {
		this->SizeBegin = SizeBegin;
		this->SizeEnd = SizeEnd;
		this->SizeDelta = SizeEnd - SizeBegin;
		this->setDuration(duration);
	}
	_Slot void onActive() {
		JUMPTIME = 0;
	}
	_Slot void onFrame() {
		JUMPTIME += getLastTime();
		if (JUMPTIME > 16) {
			QSize Size = SizeBegin + this->getPercent(VIDuration::PercentType::Linear) * SizeDelta;
			emit getSize(Size);
			JUMPTIME = 0;
		}
	}
	_Slot void onDone() {
		emit getSize(SizeEnd);
	}
	_Slot void onSkip() {
		emit getSize(SizeEnd);
	}
};

class VIResizeAnimation :public VIAnimationEvent
{
	Q_OBJECT
signals:
	void getSize(QSize);
public:
	QSize Begin;
	QSize End;
	QSize Delta;
	VIResizeAnimation INIT{
	}
	void setSize(QSize begin, QSize end, int ms, bool wait) {
		Begin = begin;
		End = end;
		Delta = QSize(qAbs(end.width() - begin.width()), qAbs(end.height() - begin.height()));
		this->setMaxMsec(ms);
		this->setDoneSignal(wait);
	}
	void event() {
		if (End.width() > Begin.width()) {
			int W = Begin.width() + Percentage * Delta.width();
			if (End.height() > Begin.height()) {
				int H = Begin.height() + Percentage * Delta.height();
				emit getSize(QSize(W, H));
			}
			else {
				int H = Begin.height() - Percentage * Delta.height();
				emit getSize(QSize(W, H));
			}
		}
		else {
			int W = Begin.width() - Percentage * Delta.width();
			if (End.height() > Begin.height()) {
				int H = Begin.height() + Percentage * Delta.height();
				emit getSize(QSize(W, H));
			}
			else {
				int H = Begin.height() - Percentage * Delta.height();
				emit getSize(QSize(W, H));
			}
		}
	}
	void onFinish() {
		emit getSize(End);
	}
	void skip() {
		emit getSize(End);
	}
	void finish() {
		emit getSize(End);
	}
};

class VIGaussianBlurAnimation :public VIAnimationEvent
{
	Q_OBJECT
public:
	int BLRadiusBegin;
	int BLRadiusEnd;
	float BLRadiusDelta;
signals:
	void getBlurs(float);
public:
	VIGaussianBlurAnimation INIT{
	}
	void setBlur(int begin, int end, int ms, bool wait) {
		BLRadiusBegin = begin;
		BLRadiusEnd = end;
		BLRadiusDelta = qAbs(end - begin);
		this->setMaxMsec(ms);
		this->setDoneSignal(wait);
	}
	void event() {
		if (BLRadiusEnd > BLRadiusBegin) {
			float BL = BLRadiusBegin + Percentage * BLRadiusDelta;
			emit getBlurs(BL);
		}
		else {
			float BL = BLRadiusBegin - Percentage * BLRadiusDelta;
			emit getBlurs(BL);
		}
	}
	void onFinish() {
		emit getBlurs(BLRadiusEnd);
	}
	void skip() {
		emit getBlurs(BLRadiusEnd);
	}
	void finish() {
		emit getBlurs(BLRadiusEnd);
	}
};
