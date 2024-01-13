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
	_Protected bool reloadAll();
	_Protected bool disablePackage(VIPackage* package);
	_Protected bool enablePackage(VIPackage* package);
	_Public VIPackage* getPackage(VIPackageUniqueName name);
	_Public QList<VIPackageUniqueName> getPackageNames();
	_Public 
};