#pragma once
#include <QtCore>
#include "VIObject.h"
#include "VIBehavior.h"
#include "VITranslationHost.h"
#include "VIPathInfo.h"
#include "VIDocument/VIJSON.h"

#define LOAD_PACKAGE(pack_name) VICoreFramework::getCoreInstance()->loadPackage(new pack_name());
class VIPackage;
class VICoreFramework;
class VIDllPackage;

class VIPublicAPI VIPackageMeta :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_MUST_INHERIT(VIPackageMeta);
	friend class VICoreFramework;
	friend class VIPackage;
	friend class VITranslationSubHost;
	friend class VITranslationHost;
	friend class VIDllPackageManager;
	_Private QString PackageName;
	_Protected VIDocument::VIJSON* PackageConfig;
	VI_ProtectedFlag(DllPackage);
	VI_ProtectedProperty(QString, DllPackagePath);
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
	_Public def_init VIPackageMeta(const QString& packageRootPath = "");
	_Public inline QString getPackageVersion() {
		return QString("%1.%2.%3").arg(PackageVersionMajor).arg(PackageVersionMinor).arg(PackageVersionPatch);
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
	_Public QString getPackageName();
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

	_Protected VIPackageMeta* PackageMeta;
	_Public def_init VIPackage();
	_Public VIPackageMeta* getPackageMeta();
	_Public void setPackageMeta(VIPackageMeta* info);
	_Public virtual void onStart() HalfVirtual;
	_Public virtual void onStop() HalfVirtual;
	_Public virtual void onTick() HalfVirtual;
	_Public virtual void onEvent(QEvent* e) HalfVirtual;
	_Public def_del ~VIPackage();
};

typedef VIPackage* (*__VisindigoDllMain)(QString);

class VIPublicAPI VIDllPackage {
	QString PackageName;
	QString DllPath;
	QLibrary* Dll = VI_NULL;
	VIPackage* Package = VI_NULL;
	_Public def_init VIDllPackage(const QString& dllpath);
	_Public Visindigo::LoadState load();
	_Public def_del ~VIDllPackage();
};

class VIPublicAPI VIDllPackageManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QList<VIDllPackage*> DllPackageList;
	_Private QString PackageRootPath;
};