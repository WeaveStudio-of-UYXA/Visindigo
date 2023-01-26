#pragma once
#include "../../../CommonEdit/CECore/CEMacro.h"
#include "macro/SPOL_m.h"
#include <QtCore>

class SPOLBaseObject {
	friend class SPOLBaseObject;
	_Public QString ObjectName = "";
	_Private int Counter = 0;
	_Private QVector<SPOLBaseObject*> QuoteList = {};
	_Public def_init SPOLBaseObject() {}
	_Public def_del ~SPOLBaseObject();
	_Public QString getObjectName();
	_Public void setObjectName(QString);
	_Public void referenceFrom(SPOLBaseObject*);
	_Public void beReferencedBy(SPOLBaseObject*);
	_Public void Unreferenced();
	
};