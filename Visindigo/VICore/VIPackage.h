#pragma once
#include <QtCore>
#include "VIObject.h"
#include "VIBehavior.h"
#include "VITranslationHost.h"
#include "VIPathInfo.h"
#include "VIDocument/VIJSON.h"
#include "VIVersion.h"

#define LOAD_PACKAGE(pack_name) VICoreFramework::getCoreInstance()->loadPackage(new pack_name());
using VIPackageUniqueName = QString;

class VIPackage;
class VICoreFramework;
class VIDllPackageContainer;

class VIPublicAPI VIPackageMeta :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_MUST_INHERIT(VIPackageMeta);
	friend class VICoreFramework;
	friend class VIPackage;
	friend class VITranslationSubHost;
	friend class VITranslationHost;
	friend class VIDllPackageContainer;
	_Private QString PackageName;
	_Private VIPackageUniqueName UniqueName; // recommend org.orgname.project.package, eg. cn.yxgeneral.visindigo.core
	_Protected QList<VIPackageUniqueName> SoftDependenceUniqueNameList;
	_Protected VIDocument::VIJSON* PackageConfig;
	_Protected QString PackageRootPath;
	VI_ProtectedProperty(unsigned int, PackageVersionMajor);
	VI_ProtectedProperty(unsigned int, PackageVersionMinor);
	VI_ProtectedProperty(unsigned int, PackageVersionPatch);
	VI_ProtectedProperty(QStringList, Author);
	VI_ProtectedProperty(QString, Description);
	VI_ProtectedProperty(QString, License);
	VI_ProtectedProperty(QString, URL);
	VI_ProtectedProperty(QString, Organization);
	VI_ProtectedProperty(QString, OrganizationDomain);
	_Protected VITranslationSubHost* TranslationPackageHost;
	_Public def_init VIPackageMeta();
	_Public inline QString getPackageVersion() {
		return QString("%1.%2.%3").arg(PackageVersionMajor).arg(PackageVersionMinor).arg(PackageVersionPatch);
	}
	_Public 
	_Public void call(const QString& funcName) {
		QMetaObject::invokeMethod(this, funcName.toLocal8Bit().data(), Qt::QueuedConnection);
	}
	_Public QString getPackageRootPath();
	_Public inline QString getPackageInternalPath() {
		return ":/package/" + PackageName;
	}
	_Public QString TR(const QString& key);
	_Public void addTranslationFileName(Visindigo::Language langType, const QString& filename, bool inRC = false);
	_Public void setDefaultLanguage(Visindigo::Language langType);
	_Public void initTranslation();
	_Public void addTranslatableObject(VITranslatableObject* obj);
	_Public void setPackageName(const QString& name);
	_Public void setPackageUniqueName(const VIPackageUniqueName& name);
	_Public QString getPackageName();
	_Public VIPackageUniqueName getPackageUniqueName();
	_Public QVariant getConfig(const QString& key);
	_Public void setConfig(const QString& key, const QVariant& value);
	_Public void saveConfig();
	_Public void initConfig();
	_Public def_del ~VIPackageMeta();
};

class VIPublicAPI VIPackage :public VIBasicBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	VI_MUST_INHERIT(VIPackage);
	friend class VIFramework;
	friend class VIDllPackageContainer;
	_Private QVector<const QMetaObject*> PackageMember;
	_Protected VIPackageMeta* PackageMeta;
	_Public def_init VIPackage();
	_Public VIPackageMeta* getPackageMeta();
	_Public void setPackageMeta(VIPackageMeta* info);
	_Public virtual void onEnable() HalfVirtual;
	_Public virtual void registerMetaInfo() HalfVirtual;
	_Public virtual void onDisable() HalfVirtual;
	_Public virtual void onReload() HalfVirtual;
	_Public virtual void onStart() HalfVirtual;
	_Public virtual void onStop() HalfVirtual;
	_Public virtual void onTick() HalfVirtual;
	_Public virtual void onEvent(QEvent* e) HalfVirtual;
	_Protected void addMember(const QMetaObject& meta);
	_Public def_del ~VIPackage();
};

using __VisindigoDllMainPtr = VIPackage* (*)(void);

#define VisindigoDllEntryPoint VisindigoDllMain
#define VisindigoDllEntryPointName "VisindigoDllMain"
#define VisindigoPlugin(PackageClassName) VIPackage* VisindigoDllEntryPoint(){ return new PackageClassName();}

class VIPublicAPI VIDllPackageContainer {
	QString PackageName;
	QString DllPath;
	QLibrary* Dll = VI_NULL;
	VIPackage* Package = VI_NULL;
	_Public def_init VIDllPackageContainer(const QString& dllpath);
	_Public Visindigo::LoadState load();
	_Public def_del ~VIDllPackageContainer();
};

/*
Visindigo Dll Package 
	- PackageFolder
		- package.json # this file describe the package info, include entry dll, package dependencies, etc.
		- 1.dll
		- 2.dll
		- ...
*/
class VIPublicAPI VIDllPackageManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QList<VIDllPackageContainer*> DllPackageList;
	_Private QString PackageRootPath;
	_Public def_init VIDllPackageManager();
	_Public void loadPackages(const QString& path);
};