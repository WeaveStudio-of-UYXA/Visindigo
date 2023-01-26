#pragma once
#include "SPOLBaseObject.h"
#include "SPOLMemoryPool.h"

class SPOLExecObject {
	_Public ENUM ExecType{
		Var,
		Func,
		Class,
		Logic,
		Memory,
	};
	_Public QString Name;
	_Public SPOLExecObject* Parent;
	_Public QVector<SPOLExecObject*> Child;
	_Public ExecType Type;
	_Public def_init SPOLExecObject(ExecType type, SPOLExecObject* parent = NULLOBJECT);
	_Public def_del ~SPOLExecObject();
	_Public def_copy SPOLExecObject(const SPOLExecObject& obj);
	_Public void setParent(SPOLExecObject*);
	_Protected void addChild(SPOLExecObject*);
	_Public void removeChild(SPOLExecObject*);
	_Public void setName(QString name);
	_Public QString getName();
	_Public QString getFullName();
	_Public SPOLExecObject* getParent();
	_Public QVector<SPOLExecObject*> getChildren();
	_Public bool hasChild(QString fullName, SPOLExecObject** returnObj);
	_Public bool hasChild(QStringList* nameList, QStringList::Iterator* name, SPOLExecObject** returnObj);
	//_Public void copyFrom(SPOLExecObject* obj);
	_Public SPOLExecObject* call(SPOLExecObject* parentEnv, SPOLExecObject* parList);
	_Public SPOLExecObject* deepCopy();
};




