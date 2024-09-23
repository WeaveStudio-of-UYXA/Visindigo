#pragma once
#include "VIAbstractObject.h"

class VIMiCoreAPI VIObject :public VISuper, VIBaseObject
{
	_Public def_init VIObject(VISuper* parent = nullptr);
};


