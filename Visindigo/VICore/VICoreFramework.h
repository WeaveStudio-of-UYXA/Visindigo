#pragma once
#include <QtCore>
#include <QtWidgets>
#include "VIPackage.h"
#include "VIObject.h"
#include "VICommand.h"
#include "VIPathInfo.h"
#include "VIMultiPlatform.h"
#include "VITranslationHost.h"

class VIPublicAPI VICoreFramework;
class VIPublicAPI private_VICoreFramework :public QApplication
{
	Q_OBJECT;
	friend class VICoreFramework;
	_Public QList<VIPackage*> PackageList = {};
	_Public int ReturnCode = 0;
	VI_Property(bool, DebugModeCompilation);
	VI_Property(bool, DebugModeRuntime);
	_Protected def_init private_VICoreFramework(int& argc, char** argv);
	_Public virtual bool notify(QObject* receiver, QEvent* e) override;
};

class VIPublicAPI VICoreFramework :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIBehaviorHost;
	friend class VITranslationHost;
	_Private static VICoreFramework* _instance;
	_Protected private_VICoreFramework* AppInstance;
	_Private static VIBehaviorHost* BehaviorHost;
	_Private static VITranslationHost* TranslationHost;
	_Private Visindigo::Language LanguageType;
	_Private QApplication* App;
	_Public def_init VICoreFramework(int& argc, char** argv);
	_Public void init();
	_Public static VIBehaviorHost* getBehaviorHostInstance();
	_Public static VITranslationHost* getTranslationHostInstance();
	_Public void start();
	_Public int getReturnCode();
	_Public bool loadPackage(VIPackage* package);
	_Public bool isDebugModeCompilation();
	_Public bool isDebugModeRuntime();
	_Public bool useDebugModeRuntime();
	_Public bool execCommand(QString);
	_Public static QApplication* getAppInstance();
	_Public static VICoreFramework* getCoreInstance();
	_Public void setLanguageType(Visindigo::Language);
	_Public Visindigo::Language getLanguageType();
	_Public QList<VIPackage*> getPackageList();
};

#define VICoreFrame VICoreFramework::getCoreInstance()
#define FrameBehaviorHost VICoreFramework::getBehaviorHostInstance()