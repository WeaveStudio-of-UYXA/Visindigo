#pragma once
#include "VIObject.h"

class VIFileTools :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_STATIC_CLASS(VIFileTools);
	_Public static QStringList filesFilter(const QString& root, const QStringList& filters, const bool considerSubDirectories = true);
};