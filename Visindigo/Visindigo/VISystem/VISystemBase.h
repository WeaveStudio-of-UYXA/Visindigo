#pragma once
#include "../../Visindigo/VIObjects/macro/VIGlassConvention.h"

namespace VIBase {
	class VISystem_Glass :public QObject
	{
		Q_OBJECT;
		publicD def_init VISystem_Glass(QObject* parent = Q_NULLPTR) :QObject(parent) {}
		slotD virtual void exit(int code = 0);
		slotD virtual QString getSystemProductName();
		slotD void print(QString str);
		slotD void wait(int ms);
		slotD QStringList argv();
	};
}