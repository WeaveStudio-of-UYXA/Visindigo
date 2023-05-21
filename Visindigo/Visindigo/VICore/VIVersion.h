#pragma once
#include "VIObject.h"
#include "private/VIAutoVersion.h"
#define VI_VERSION_MAJOR 0
#define VI_VERSION_MINOR 10
#define VI_VERSION_PATCH 0
#define VI_VERSION_NICKNAME "It's all broken"
class VIVersion :public VIObject {
	Q_OBJECT;
	_Public static QString getVisindigoVersion() { return QString::number(VI_VERSION_MAJOR) + "." + QString::number(VI_VERSION_MINOR) + "." + QString::number(VI_VERSION_PATCH)+"."+QString::number(VI_VERSION_BUILD); }
	_Public static QString getVisindigoNickname() { return QString(VI_VERSION_NICKNAME); }
	_Public static QString getVisindigoCompileTime() { return QString(__DATE__) + " " + QString(__TIME__); }
	_Public static QString getVisindigoQtVersion() { return QString(QT_VERSION_MAJOR) + "." + QString(QT_VERSION_MINOR); }
};