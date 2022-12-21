#pragma once
#include "VIGuiAnimation.h"
#include "VIMath.h"
#include "Visindigo/VIObjects/VIObject/VIObject.h"
class VITextAnimation : public VIAnimationEvent
{
	Q_OBJECT
signals:
	void getText(QString);
public:
	QString Text;
	QString Output;
	QString LastText;
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
		LastText = "";
	}
	void continueText(QString text) {
		this->Output = this->Text;
		this->Text = text;
		this->setMaxMsec(Text.length() * MSPT + MSW);
		Char = Text.begin();
		LastText = Output;
	}
	void setSpeed(int MsPT) {
		this->MSPT = MsPT;
	}
	void setWait(int MsW) {
		this->MSW = MsW;
	}
	void event() {
		if (getCurrentMsec() >= LMS && Char != Text.end() && !SKIPED) {
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
		emit getText(LastText + Text);
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
	void onFinish() {
		emit getOpacity(OPEnd);
	}
	void skip() {
		emit getOpacity(OPEnd);
	}
	void finish() {
		emit getOpacity(OPEnd);
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