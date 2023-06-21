#pragma once
#include <QtQml>
#include <QtCore>
#include "../../VICore/macro/VIMarco.h"
#include "../../VICore/VIObject.h"
#include "../../VICore/VIBehavior.h"

class VIES_Behavior :public VIBasicBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QJSValue* ESBehavior;
	_Public def_init VIES_Behavior(QJSValue* value, VISuper* parent = VI_NULLPTR) :VIBasicBehavior(parent) {
		ESBehavior = value;
	}
	_Public void onActive() {
		QJSValue func = ESBehavior->property("onActive");
		func.callWithInstance(*ESBehavior);
	}
	_Public void onPassive() {
		QJSValue func = ESBehavior->property("onPassive");
		func.callWithInstance(*ESBehavior);
	}
	_Public void onTick() {
		QJSValue func = ESBehavior->property("onTick");
		func.callWithInstance(*ESBehavior);
	}
};