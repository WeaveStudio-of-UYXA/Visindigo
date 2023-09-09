﻿#pragma once
#include "VIObject.h"
#include "private/VIAutoVersion.h"
#define VI_VERSION_MAJOR 1
#define VI_VERSION_MINOR 2
#define VI_VERSION_PATCH 0

class VIPublicAPI VIVersion :public VIObject {
	Q_OBJECT;
	_Public static const QString getVisindigoVersion() { return QString::number(VI_VERSION_MAJOR) + "." + QString::number(VI_VERSION_MINOR) + "." + QString::number(VI_VERSION_PATCH) + "." + QString::number(VI_VERSION_BUILD); }
	_Public static const QString getVisindigoNickname() { return QString(VI_VERSION_NICKNAME); }
	_Public static const QString getVisindigoCompileTime() { return QString(VI_VERSION_BUILD_DATE) + " " + QString(VI_VERSION_BUILD_TIME); }
	_Public static const QString getVisindigoQtVersion() { return QString::number(QT_VERSION_MAJOR) + "." + QString::number(QT_VERSION_MINOR); }
};