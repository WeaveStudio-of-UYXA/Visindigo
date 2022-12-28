#pragma once
#include "../../Visindigo/VIObjects/macro/VIGlassConvention.h"

namespace VIBase {
	class VISystem_Glass :public QObject
	{
		Q_OBJECT;
		pPublic def_init VISystem_Glass(QObject* parent = Q_NULLPTR) :QObject(parent) {}
		pSlot virtual void exit(int code = 0);
		pSlot virtual QString getSystemProductName();
		pSlot void print(QString str);
		pSlot void wait(int ms);
		pSlot QStringList argv();
	};
}