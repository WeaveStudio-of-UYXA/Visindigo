#pragma execution_character_set("utf-8")
#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "SPDF.h"
#include <iostream>
#include <string>
/*
SPDFClassicTester
在YSP0.4（大概？）等没有UI的版本中，我们用了命令行测试SPDF功能。
后来做了UI之后这个功能被移除（Python版没删干净，但C++版是一点不带剩的）
我们现在要把它重新加回来
*/

class SPDFTestAnimation_Text :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void finished();
	_Public QString CurrentText;
	_Public std::string RawText;
	_Public int index;
	_Public VIMilliSecond CurrentTime;
	_Public VIMilliSecond TextMaxTime;
	_Public def_init SPDFTestAnimation_Text(VISuper* parent) :VIAnimationBehavior(parent) {
	}
	_Public void setTextAnimation(QString text, double spc, double swl) {
		VISecond s = text.length() * spc + swl;
		TextMaxTime = text.length() * spc * 1000;
		RawText = text.toStdString();
		this->setDuration(s * 1000);
	}
	_Public void onActive() override {
		CurrentText = "";
		CurrentTime = 0;
		index = 0;
	}
	_Public void onTick() override {
		CurrentTime += getTickDuration();
		int cIndex = RawText.length() * CurrentTime / TextMaxTime;
		if (cIndex > RawText.length()) { return; }
		if (cIndex > index) {
			for (; index < cIndex; index++) {
				std::cout << RawText[index];
			}
		}
	}
	_Public void onPassive() override {
		std::cout << std::endl;
		emit finished();
	}
};
class SPDFClassicTester :public SPDFAbstractTerminal
{
	Q_OBJECT;
	VI_OBJECT;
	_Public SPDFTestAnimation_Text* TextAnimation;
	_Public def_init SPDFClassicTester(VISuper* parent = VI_NULLPTR) {
		TextAnimation = new SPDFTestAnimation_Text(this);
		connect(TextAnimation, &SPDFTestAnimation_Text::finished, this, &SPDFClassicTester::controllerHandled);
	}
	_Slot void onControllers(SPDFParserResultList* list) override {
		consoleLog("get controllers, count: " + QString::number(list->length()) + ".");
		bool noController = true;
		for (auto i = list->begin(); i != list->end(); i++) {
			consoleLog("controller: " + i->MethodName);
			for (auto j = i->Parameters.begin(); j != i->Parameters.end(); j++) {
				consoleLog("parameter: " + j.key() + ", value: " + j->toString());
			}
			if (i->MethodName == "YSP.10X.Speaking") {
				noController = false;
				TextAnimation->setTextAnimation(i->Parameters["Text"].toString(), i->Parameters["SecondPerChar"].toDouble(), i->Parameters["SecondLineEnd"].toDouble());
				TextAnimation->active();
				continue;
			}
		}
		if (noController) { emit controllerHandled(); }
	}
};