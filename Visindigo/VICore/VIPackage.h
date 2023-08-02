#pragma once
#include <QtCore>
#include "VIObject.h"
#include "VIBehavior.h"
#include "VITranslationHost.h"
#include "VIPathInfo.h"
#include "VIDocument/VIJSON.h"

#define LOAD_PACKAGE(pack_name) VICoreFramework::getCoreInstance()->loadPackage(new pack_name());
class VIPublicAPI VIPackage;
class VIPublicAPI VICoreFramework;

class VIPublicAPI VIPackageMeta :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_MUST_INHERIT(VIPackageMeta);
	friend class VICoreFramework;
	friend class VIPackage;
	friend class VITranslationSubHost;
	friend class VITranslationHost;
	_Private QString PackageName;
	_Private VIDocument::VIJSON* PackageConfig;
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
	_Public inline QString getPackageRootPath() {
		return VIPathInfo::getProgramPath() + "/package/" + PackageName;
	}
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
	_Public void initConfig();
	_Public def_del ~VIPackageMeta();
};

class VIPublicAPI VIPackage :public VIBasicBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	VI_MUST_INHERIT(VIPackage);
	friend class VIFramework;
	_Private VIPackageMeta* PackageMeta;
	_Public def_init VIPackage();
	_Public VIPackageMeta* getPackageMeta();
	_Public void setPackageMeta(VIPackageMeta* info);
	_Public virtual void onActive() HalfVirtual;
	_Public virtual void onSubside() HalfVirtual;
	_Public virtual void onTick() HalfVirtual;
	_Public virtual void onEvent(QEvent* e) HalfVirtual;
	_Public def_del ~VIPackage();
};

typedef VIPackage* (* __VisindigoDllMain)(void);