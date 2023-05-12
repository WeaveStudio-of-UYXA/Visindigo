#pragma once
#include <QtQml>
#include <QtCore>
#include "../../VICore/macro/VIMarco.h"
#include "../../VICore/VIObject.h"

class VIECMAFunction :public VIObject, QJSValue
{
	Q_OBJECT;
	VI_OBJECT;
};
