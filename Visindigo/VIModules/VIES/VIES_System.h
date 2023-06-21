#pragma once
#include <QtQml>
#include <QtCore>
#include "../../VICore/macro/VIMarco.h"
#include "../../VICore/VIObject.h"
#include "../../VICore/VISystem.h"
class VIES_System :public VISystem
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIES_System(VISuper* parent = VI_NULLPTR) :VISystem(parent) {};
	_Slot void log(QString logstr) { consoleLog(logstr); }
};