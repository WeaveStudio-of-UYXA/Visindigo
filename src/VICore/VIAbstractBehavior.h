#pragma once
#include <VIMiCore>
#include "VICoreCompileMacro.h"

class VICoreAPI VIAbstractBehavior :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIAbstractBehavior(QString name, VISuper* parent = nullptr);
	_Public virtual void onStart();
	_Public virtual void onEnd();
};
