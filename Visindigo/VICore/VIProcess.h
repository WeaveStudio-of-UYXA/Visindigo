#pragma once
#include "VIObject.h"

class VIProcess :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QProcess* Process;
};