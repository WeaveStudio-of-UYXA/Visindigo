#pragma execution_character_set("utf-8")
#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "SPDF.h"
/*
SPDFClassicTester
在YSP0.4（大概？）等没有UI的版本中，我们用了命令行测试SPDF功能。
后来做了UI之后这个功能被移除（Python版没删干净，但C++版是一点不带剩的）
我们现在要把它重新加回来
*/

class SPDFClassicTester :public SPDFAbstractTerminal
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init SPDFClassicTester(VISuper* parent = VI_NULLPTR) {
		
	}
	_Slot void onControllers(SPDFParserObjectList* list) override {
		consoleLog("get controllers, count: " + QString(list->length()));
		for (auto i = list->begin(); i != list->end(); i++) {
			consoleLog("controller: "+i->MethodName);
			for (auto j = i->Parameters.begin(); j != i->Parameters.end(); j++) {
				consoleLog("parameter: " + j.key()+", value: "+j->toString());
			}
		}
		emit controllerHandled();
	}
};