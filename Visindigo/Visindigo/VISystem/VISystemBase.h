#pragma once
#include "../../Visindigo/VIObjects/VIObject/VIGlassObject.h"

namespace VIBase {
	class VISystem_Glass :public VIGlassObject
	{
		Q_OBJECT;
		Public def_init VISystem_Glass(QObject* parent = Q_NULLPTR) :VIGlassObject(parent) {}
		Slot virtual void exit(int code = 0);
		Slot virtual QString getSystemProductName();
		Slot void print(QString str);
		Slot void wait(int ms);
		Slot QStringList argv();
	};
}