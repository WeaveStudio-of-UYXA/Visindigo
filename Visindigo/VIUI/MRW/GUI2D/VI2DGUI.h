#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "../../../../Visindigo/VICore/VIGuiAnimation.h"
#include "../MRWGlobal.h"

class VITextAnimation : public VIAnimationEvent
{
	Q_OBJECT
signals:
	void getText(QString);
public:
	QString Text;
	QString Output;
	int MSPT;
	int MSW;
	int INDEX;
	float TEXTPERCENT;
	float LMS;
	QString::iterator Char;
	VITextAnimation INIT{
		MSPT = 300;
		MSW = 1500;
		INDEX = 0;
		LMS = 0;
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
		this->MSW = MSW;
	}
	void event() {
		if (CurrentMsec >= LMS && Char != Text.end()) {
			Output += *Char;
			Char++;
			INDEX++;
			LMS = INDEX * MSPT;
			emit getText(Output);
		}
	}
};
class VITextObject : public QLabel 
{

};