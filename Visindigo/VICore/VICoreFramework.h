#pragma once
#include <QtCore>
#include <QtWidgets>
#include "VIPackage.h"
#include "VIException.h"
#include "VIObject.h"
#include "VIConsole.h"
#include "VICommand.h"
#include "VIPathInfo.h"
#include "VIMultiPlatform.h"
#include "VILanguage.h"
#include "VIVersion.h"
#include "VIECMAScripts.h"
#define FrameBehaviorHost VICoreFramework::getBehaviorHostInstance()
class VIPublicAPI VICoreFramework;
class VIPublicAPI private_VICoreFramework :public QApplication
{
	Q_OBJECT;
	friend class VICoreFramework;
	_Public QList<VIPackage*> PackageList = {};
	_Public int ReturnCode = 0;
	VI_Property(bool, DebugModeCompilation);
	VI_Property(bool, DebugModeRuntime);
	_Protected def_init private_VICoreFramework(int& argc, char** argv) :QApplication(argc, argv) {};
	_Public virtual bool notify(QObject* receiver, QEvent* e) {
		try {
			return QApplication::notify(receiver, e);
		}
		catch (VIException& e) {
			e.print();
			VIMultiPlatform::exit();
			return false;
		}
		return true;
	}
};

class VIPublicAPI VICoreFramework :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private static VICoreFramework* _instance;
	_Private private_VICoreFramework* AppInstance;
	_Private static VIBehaviorHost* BehaviorHost;
	_Private static VILanguageHost* LanguageHost;
	_Private QApplication* App;
	_Public def_init VICoreFramework(int& argc, char** argv);
	_Public void init();
	_Public static VIBehaviorHost* getBehaviorHostInstance();
	_Public static VILanguageHost* getLanguageHostInstance();
	_Public void start();
	_Public int getReturnCode();
	_Public bool loadPackage(VIPackage* package);
	_Public bool isDebugModeCompilation();
	_Public bool isDebugModeRuntime();
	_Public bool useDebugModeRuntime();
	_Public static bool execCommand(QString);
	_Public static QApplication* getAppInstance();
	_Public static VICoreFramework* getCoreInstance();
};
#define VICoreFrame VICoreFramework::getInstance()