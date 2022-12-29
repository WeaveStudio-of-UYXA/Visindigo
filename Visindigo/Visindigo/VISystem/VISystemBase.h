#pragma once
#include "../../Visindigo/VIObjects/macro/VIGlassConvention.h"

namespace VIBase {
	class VISystem_Glass :public QObject
	{
		Q_OBJECT;
		Public_ def_init VISystem_Glass(QObject* parent = Q_NULLPTR) :QObject(parent) {}
		Slot_ virtual void exit(int code = 0);
		Slot_ virtual QString getSystemProductName();
		Slot_ void print(QString str);
		Slot_ void wait(int ms);
		Slot_ QStringList argv();
	};
}