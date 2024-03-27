#pragma once
#include "VIPackage.h"

class VICoreFramework;
class VIPublicAPI VIPackageManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VICoreFramework;
	VI_Singleton(VIPackageManager);
	_Private QMap<VIPackageUniqueName, VIPackage*> Packages;
	_Private QMap<VIPackageUniqueName, VIDllPackageContainer*> DllPackages;
	_Public def_init VIPackageManager(VISuper* parent = VI_NULL);
	_Public bool loadPackage(VIPackage* package);
	_Public bool loadPluginPackages(QString rootPath);
	_Protected bool startAll();
	_Protected bool disableAll();
	_Protected bool reloadAll(); // just 'soft' reload, such as reload package config, clear temp data, etc.
	_Protected bool reInitAll(); // 'hard' reload, means release the dll then reload it, useful for debug. Just for soft package.
	_Protected bool disablePackage(VIPackageUniqueName packageName);
	_Protected bool enablePackage(VIPackageUniqueName package);
	_Public VIPackage* getPackage(VIPackageUniqueName name);
	_Public QList<VIPackageUniqueName> getPackageNames();
	_Public 
};