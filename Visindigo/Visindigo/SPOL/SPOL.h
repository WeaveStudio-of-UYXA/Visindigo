#pragma once
#include "SPOLObject.h"

class SPOLInterpreter :public QObject {
	Q_OBJECT;
	_Public QString Version = "10.0";
	_Public def_init SPOLInterpreter(QObject* parent = Q_NULLPTR) :QObject(parent) {}
	_Public bool exec(QString);
	_Public bool exec(SPOLExecObject*);
	_Public bool execFile(QString);
};