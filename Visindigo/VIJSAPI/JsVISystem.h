﻿#pragma once
#include <QtCore>
#include "Visindigo/VISystem/VISystemBase.h"

namespace JsVI
{
	class VISystem :public VIBase::VISystem_Glass
	{
		Q_OBJECT;
		pPublic def_init VISystem(QObject* parent = Q_NULLPTR) :VIBase::VISystem_Glass(parent) {}
	};
}