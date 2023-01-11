#pragma once
#include <QtCore>
#include "../VISystem/VISystemBase.h"

namespace JsVI
{
	class VISystem :public VIBase::VISystem_Glass
	{
		Q_OBJECT;
		_Public def_init VISystem(QObject* parent = Q_NULLPTR) :VIBase::VISystem_Glass(parent) {}
	};
}