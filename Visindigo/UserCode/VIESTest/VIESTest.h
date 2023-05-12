#pragma once
#include "../../Visindigo/VICore/VIPackage.h"
#include "../../Visindigo/VIModules/VIES/VIECMAScripts.h"

class VIESTest :public VIPackage
{
	Q_OBJECT;
	_Public def_init VIESTest(QObject* parent = nullptr) {
		consoleLog("VIESTest init");
		VIECMAScripts* scripts = new VIECMAScripts();
		scripts->setUserMain("../Visindigo/Dev/test2.js");
		QJSValue r = scripts->boot("aplus");
		consoleLog("1st "+r.toString());
		r = scripts->boot("aplus");
		consoleLog("2nd "+r.toString());
		r = scripts->boot("aplus");
		consoleLog("3rd "+r.toString());
	};
};