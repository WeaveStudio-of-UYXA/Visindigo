#pragma once
#include <QtCore>
#include "macro/VIMarco.h"
#include "VIMainBehavior.h"

#define LOAD_PACKAGE(pack_name) VIFramework::Instance->loadPackage(new pack_name());
class VIFramework;
class VIPackage :public VIMainBehavior
{
	_Public QString PackageName;
	_Public VIFramework* Framework;
	_Public def_init VIPackage() {};
	_Public virtual void onActive() {};
	_Public virtual void onExit() {};
	_Public virtual void onFrame() {};
	_Public virtual void onEvent(QEvent* e) {};
};