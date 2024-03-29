﻿#pragma once
#include "VIObject.h"
#include <QtWidgets>

class VIPublicAPI VIMultiPlatform {
	VI_STATIC_CLASS(VIMultiPlatform);
	_Public static void exit() { QCoreApplication::exit(); }
	_Public static QString getSystemName() { return QSysInfo::prettyProductName(); }
	_Public static QString getSystemType() { return QSysInfo::productType(); }
	_Public static QString getSystemVersion() { return QSysInfo::productVersion(); }
	_Public static QStringList argv() { return qApp->arguments(); }
	_Public static QString getBuildAbi() { return QSysInfo::buildAbi(); }
	_Public static QString getCPUBuildType() { return QSysInfo::buildCpuArchitecture(); }
	_Public static QString getCPUCurrentType() { return QSysInfo::currentCpuArchitecture(); }
	_Public static QString getSystemKernelType() { return QSysInfo::kernelType(); }
	_Public static QString getSystemKernelVersion() { return QSysInfo::kernelVersion(); }
	_Public static QColor getSystemThemeColor() { return static_cast<QApplication*>(QApplication::instance())->palette().color(QPalette::Window); }
};