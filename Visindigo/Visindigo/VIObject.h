#pragma once
#include "VIMacro.h"
#include <QtCore>

struct VIObject
{
	VIObject* Parent;
	QList<VIObject*> Children;
	QString Name;
	QString Type;
	VIObject* OnCall;
	QStringList CallType;
};

