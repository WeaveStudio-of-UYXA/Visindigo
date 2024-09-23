#pragma once
#include "../VIMiCoreFramework.h"
class VILoggerManager;
class VIPackageManager;
class VIMiCoreAPI VICoreFrameworkPrivate
{
	friend class VIMiCoreFramework;
	friend class VIGuiFramework;
	friend class VIFramework;
	friend class VIQCoreApplication;
	friend class VIQGuiApplication;
	friend class VIQApplication;

	_Protected static VIMiCoreFramework* Instance;

	_Protected bool onException(const std::exception& e);

	_Protected void* VIQAppInstance = nullptr;
	_Protected VILoggerManager* LoggerManager = nullptr;
	_Protected VIPackageManager* PackageManager = nullptr;
};