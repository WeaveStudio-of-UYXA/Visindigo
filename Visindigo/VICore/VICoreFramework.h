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
	_Protected QMap<VIPackageUniqueName, VIPackage*> PackageMap = {};
	_Public int ReturnCode = 0;
	VI_Property(bool, DebugModeCompilation);
	VI_Property(bool, DebugModeRuntime);
	_Protected def_init private_VICoreFramework(int& argc, char** argv);
	_Protected virtual bool notify(QObject* receiver, QEvent* e) override;
};

class VIPublicAPI VICoreFramework :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIBehaviorHost;
	friend class VITranslationHost;
	_Private static VICoreFramework* _instance;	
	_Private static VIBehaviorHost* BehaviorHost;
	_Private static VITranslationHost* TranslationHost;
	_Protected private_VICoreFramework* PrivateCoreFramework;
	_Private Visindigo::Language LanguageType;
	_Public static VIBehaviorHost* getBehaviorHostInstance();
	_Public static VITranslationHost* getTranslationHostInstance();
	_Public static QApplication* getQAppInstance();
	_Public static VICoreFramework* getCoreInstance();
	_Public def_init VICoreFramework(int& argc, char** argv);
	_Public void init();
	_Public void start();
	_Public int getReturnCode();
	_Public bool loadPackage(VIPackage* package);
	_Public bool isDebugModeCompilation();
	_Public bool isDebugModeRuntime();
	_Public bool useDebugModeRuntime();
	_Public bool execCommand(QString);
	_Public void setLanguageType(Visindigo::Language);
	_Public Visindigo::Language getLanguageType();
	_Public QList<VIPackage*> getPackageList();
	_Public bool softCall(const QString& uniqueName, const QString& methodName, QVariantList& args, QGenericReturnArgument& result);
};

#define VICoreFrame VICoreFramework::getCoreInstance()
#define FrameBehaviorHost VICoreFramework::getBehaviorHostInstance()