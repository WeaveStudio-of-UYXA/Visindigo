#pragma once
#include "../../../CommonEdit/CECore/CEMacro.h"
#include "macro/SPOL_m.h"
#include <QtCore>

class SPOLExecObject {
	_Public ENUM ExecType{
		Var = 0,
		Func = 1,
		Class = 2,
		Logic = 3
	};
	_Public QString Name;
	_Public SPOLExecObject* Parent;
	_Public QList<SPOLExecObject*> Child;
	_Public ExecType Type;
	_Public def_init SPOLExecObject(ExecType type, SPOLExecObject* parent = NULLOBJECT);
	_Public def_del ~SPOLExecObject();
	_Public def_copy SPOLExecObject(const SPOLExecObject& obj);
	_Public void setParent(SPOLExecObject*);
	_Protected void addChild(SPOLExecObject*);
	_Protected void removeChild(SPOLExecObject*);
	_Public void setName(QString name);
	_Public QString getName();
	_Public SPOLExecObject* getParent();
	_Public QList<SPOLExecObject*> getChildren();
	_Public bool hasChild(QString fullName, SPOLExecObject** returnObj);
	_Public bool hasChild(QStringList* nameList, QStringList::Iterator* name, SPOLExecObject** returnObj);
	//_Public void copyFrom(SPOLExecObject* obj);
	_Public SPOLExecObject* exec(SPOLExecObject*);
};
