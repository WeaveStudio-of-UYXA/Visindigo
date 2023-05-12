#pragma once
#include <QtCore>
#include "macro/VIMarco.h"
#include "VIObject.h"

class VISystem :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VISystem(VISuper* parent = VI_NULLPTR) :VIObject(parent) {};
	_Slot static QString getSystemName() { return QSysInfo::prettyProductName(); }
	_Slot static QString getSystemType() { return QSysInfo::productType(); }
	_Slot static QString getSystemVersion() { return QSysInfo::productVersion(); }
	_Slot static QStringList argv() { return qApp->arguments(); }
	_Slot static QString getVisindigoCompileTime() { return QString(__DATE__) + " " + QString(__TIME__); }
	_Slot static QString getVisindigoQtVersion() { return QString(QT_VERSION_MAJOR) + "." + QString(QT_VERSION_MINOR); }
	_Slot static QString getBuildAbi() { return QSysInfo::buildAbi(); }
	_Slot static QString getCPUBuildType() { return QSysInfo::buildCpuArchitecture(); }
	_Slot static QString getCPUCurrentType() { return QSysInfo::currentCpuArchitecture(); }
	_Slot static QString getSystemKernelType() { return QSysInfo::kernelType(); }
	_Slot static QString getSystemKernelVersion() { return QSysInfo::kernelVersion(); }
	_Slot static void wait(int ms) { QThread::msleep(ms); }
};