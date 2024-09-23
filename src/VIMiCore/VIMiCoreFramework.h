#pragma once
#include "VIObject.h"
#include "VILogger.h"

class VICoreFrameworkPrivate;
class VIQCoreApplication;
class VIQGuiApplication;
class VIQApplication;
class VIMiCoreAPI VIMiCoreFramework :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;

	friend class VIFrameworkPrivate;
	friend class VIQCoreApplication;
	friend class VIQGuiApplication;
	friend class VIQApplication;

	_Public static VIMiCoreFramework* Instance();
	_Public def_init VIMiCoreFramework(int& argc, char** argv);
	_Public def_copy VIMiCoreFramework(const VIMiCoreFramework& other) = delete;
	_Public def_move VIMiCoreFramework(VIMiCoreFramework&& other) = delete;
	_Public def_del ~VIMiCoreFramework();

	_Public VILogger* logger(const QString& name = "");
	_Public void setLoggerLevel(VILogger::Level level);
	_Public void init();
	_Public void exec();
	_Protected VICoreFrameworkPrivate* d;
};