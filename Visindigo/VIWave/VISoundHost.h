#pragma once
#include "../VICore/VIObject.h"
#include <QtMultimedia>

class VISoundHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VISoundHost(VISuper* parent = VI_NULL):VIObject(parent) {
		
	}
};