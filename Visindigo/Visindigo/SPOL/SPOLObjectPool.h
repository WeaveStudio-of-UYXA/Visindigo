#pragma once
#include "SPOLObject.h"

class SPOLObjectPool :public QObject {
	Q_OBJECT;
	_Public SPOLExecObject* ExecMain;
	_Public QVector<SPOLExecObject*> DefPool;
	_Public QVector<SPOLExecObject*> RunPool;
	_Public void setExecMain(SPOLExecObject* main);
	_Private bool hasDefObject(QString name, SPOLExecObject** returnObj);
	_Public void addDefObjectTo(SPOLExecObject* defObj, SPOLExecObject* parent);
	_Public void addDefObjectTo(SPOLExecObject* defObj, QString parentName);
	_Public void addRunObject(SPOLExecObject* runObj, QString runName);
};