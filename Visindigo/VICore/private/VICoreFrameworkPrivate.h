#pragma once
#include "../VICoreFramework.h"

class VIPrivateAPI VICoreFrameworkPrivate {
	friend class VICoreFramework;
	_Protected QMap<VIPackageUniqueName, VIPackage*> PackageMap = {};
};