#pragma once
#include "SPOLObject.h"

class SPOLObjectPool {
	_Public SPOLExecObject* ExecMain;
	_Public QVector<SPOLExecObject*> DefPool;
	_Public void setExecMain(SPOLExecObject* main);
	_Public bool hasDefObject(QString name, SPOLExecObject** returnObj);
	_Public void addDefObject(SPOLExecObject* defObj);
	_Public void addDefObjectTo(SPOLExecObject* defObj, SPOLExecObject* parent);
	_Public void addDefObjectTo(SPOLExecObject* defObj, QString parentName);
};