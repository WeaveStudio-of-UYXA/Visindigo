#pragma once
#include "../../Visindigo/VIObjects/macro/VIGlassConvention.h"

namespace VIBase {
	class VISystem_Glass :public QObject
	{
		Q_OBJECT;
		_Public def_init VISystem_Glass(QObject* parent = Q_NULLPTR) :QObject(parent) {}
		_Slot virtual void exit(int code = 0);
		_Slot virtual QString getSystemProductName();
		_Slot void print(QString str);
		_Slot void wait(int ms);
		_Slot QStringList argv();
	};
}