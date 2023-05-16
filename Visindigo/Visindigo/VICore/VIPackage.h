#pragma once
#include <QtCore>
#include "VIObject.h"
#include "VIBehavior.h"

#define LOAD_PACKAGE(pack_name) VIFramework::getInstance()->loadPackage(new pack_name());
class VIFramework;
class VIPackage :public VIBasicBehavior
{
	_Public QString PackageName;
	_Public VIFramework* Framework;
	_Public def_init VIPackage(VISuper* parent = VI_NULLPTR) :VIBasicBehavior(parent) {};
	_Public virtual void onActive() {};
	_Public virtual void onPassive() {};
	_Public virtual void onTick() {};
	_Public virtual void onEvent(QEvent* e) {};
};