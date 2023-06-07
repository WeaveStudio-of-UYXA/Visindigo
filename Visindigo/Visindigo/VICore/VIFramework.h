#pragma once
#include <QtCore>
#include <QtWidgets>
#include "VIPackage.h"
#include "VIException.h"
#include "VIObject.h"
#include "VIConsole.h"
#include "VICommand.h"
#include "VIDocument.h"
#include "VIMultiPlatform.h"
#include "VILanguage.h"
#include "VIVersion.h"
#include "VIECMAScripts.h"
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
class VIApplication :public QApplication
{
	Q_OBJECT;
	_Public def_init VIApplication(int& argc, char** argv) :QApplication(argc, argv) {};
	_Public virtual bool notify(QObject* receiver, QEvent* e) {
		try {
			return QApplication::notify(receiver, e);
		}
		catch (VIException& e) {
			e.print();
			VIMultiPlatform::exit();
		}
	}
};
class VIFramework :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private private_VIFramework* Data;
	_Private static VIFramework* Instance;
	_Private static VIBehaviorHost* BehaviorHost;
	_Private static VILanguageHost* LanguageHost;
	_Private QApplication* App;
	_Public def_init VIFramework(int& argc, char** argv);
	_Public void init();
	_Public static VIBehaviorHost* getBehaviorHostInstance();
	_Public static VILanguageHost* getLanguageHostInstance();
	_Public void start();
	_Public static VIFramework* getInstance();
	_Public int getReturnCode();
	_Public bool loadPackage(VIPackage* package);
	_Public bool isDebugModeCompilation();
	_Public bool isDebugModeRuntime();
	_Public bool useDebugModeRuntime();
	_Public static bool execCommand(QString);
};