﻿#pragma once
#include "../VICore/VICore.h"
struct VIDifferenceData
{
	QMap<quint32, quint32> InsertedLines; // <line, count>
	QList<quint32> RemovedLines; // <line>
	QList<quint32> ChangedLines; // <line>
};
class VIDifferenceAnalyzer :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QStringList CurrentDocument;
	_Private QStringList PreviousDocument;
};