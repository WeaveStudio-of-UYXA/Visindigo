#pragma once
#include <QtCore>
#include <QtWidgets>
#include "VIPackage.h"
#include "VIObject.h"
#include "VIConsole.h"
#include "VIMultiPlatform.h"
#include "VIVersion.h"
#define FrameBehaviorHost VIFramework::getBehaviorHostInstance()
class VIFramework;
class private_VIFramework :public VIObject
{
	Q_OBJECT;
	friend class VIFramework;
	_Public QList<VIPackage*> PackageList = {};
	_Public int ReturnCode = 0;
	VI_Property(bool, DebugModeCompilation);
	VI_Property(bool, DebugModeRuntime);
};
class VIFramework :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private private_VIFramework* Data;
	_Private static VIFramework* Instance;
	_Private static VIBehaviorHost* BehaviorHost;
	_Private QApplication* App;
	_Public def_init VIFramework(int& argc, char** argv);
	_Public void init();
	_Public static VIBehaviorHost* getBehaviorHostInstance();
	_Public void start();
	_Public static VIFramework* getInstance();
	_Public int getReturnCode();
	_Public bool loadPackage(VIPackage* package);
	_Public inline bool isDebugModeCompilation();
	_Public inline bool isDebugModeRuntime();
	_Public inline bool useDebugModeRuntime();
};