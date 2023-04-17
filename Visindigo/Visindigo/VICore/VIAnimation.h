#pragma once
#include "VIGeneralBehavior.h"
#include "VIMainBehavior.h"
#include "VIBehavior.h"
/*
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
*/
class VIAnimationBehavior :public VITimedBehavior
{

};
class VIGuiAnimation :public VITimedBehavior
{
	Q_OBJECT;
	_Private bool WAITFLAG;
	_Public bool StateSkip = false;
	_Private QLabel* LABEL;
	_Public def_init VIGuiAnimation(QObject* parent = Q_NULLPTR) :VITimedBehavior(parent) {}
	_Public bool ifWait() {
		return this->WAITFLAG;
	};
	_Public void setWait(bool w) {
		this->WAITFLAG = w;
	}
	_Public VIMilliSecond getLastTime() { return VITimedBehavior::getTickDuration(); }
	_Public VIMilliSecond getCurrent() { return (double)(this->Duration->getElapse()) / 1000000.0; }
	_Public float getPercent() { return this->Duration->getPercent(); }
	_Public void onTick() {
		if (this->StateSkip) {
			this->onSkip();
		}
		else {
			this->onFrame();
		}
	}
	_Public void onPassive() {
		this->onDone();
	}
	_Public virtual void onFrame() {};
	_Public virtual void onSkip() {};
	_Public virtual void onDone() {};
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
		qDebug() << this->getDuration()->getDuration();
		qDebug() << this->BEFORE;
		qDebug() << this->TEXT;
		qDebug() << this->MSPT;
		qDebug() << this->MSW;

	}
	_Protected void onActive() {
		LMS = 0;
		INDEX = 0;
		CHAR = TEXT.begin();
	}
	_Protected void onFrame() {
		//qDebug() << getCurrent();
		//getLastTime();
		if (getCurrent() >= LMS && CHAR != TEXT.end() ) {
			CURRENT += *CHAR;
			CHAR++;
			INDEX++;
			LMS = INDEX * MSPT;
			
			emit getText(CURRENT);
		}
		//qDebug() << "Percent" << this->getPercent(VIDuration::PercentType::Linear) << "Duration" << this->getDuration();
	}
	_Protected void onSkip() {
		qDebug() << "Skip";
		CHAR = TEXT.end();
		//this->setDuration(TEXT.length() * MSPT);
		emit getText(BEFORE + TEXT);
	}
	_Protected void onDone() {
		qDebug() << "Done";
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
		float OP = OPBegin + this->getPercent() * OPDelta;
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
			QSize Size = SizeBegin + this->getPercent() * SizeDelta;
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


