#pragma once
#include "VIMacro.h"
#include <QtCore>

typedef QObject VISuper;

class VIMiCoreAPI VIAbstractObject
{

};

typedef VIAbstractObject VIBaseObject;

#define VI_OBJECT p_VI_OBJECT_CONTENT

#define p_VI_OBJECT_CONTENT 