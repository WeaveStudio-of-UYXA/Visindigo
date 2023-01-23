#pragma once
#include "../../../CommonEdit/CECore/CEMacro.h"
#include "macro/SPOL_m.h"
#include <QtCore>

class SPOLBaseObject {
	_Public QString ObjectName;
	_Public virtual SPOLBaseObject* call(SPOLBaseObject* parent, SPOLBaseObject* para) {};
	_Public QString getObjectName();
	_Public void setObjectName();
};