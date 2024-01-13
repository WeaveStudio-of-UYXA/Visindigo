#pragma once
#include <QtCore>
#include "VIObject.h"
#include "VIBehavior.h"
#include "VITranslationHost.h"
#include "VIPathInfo.h"
#include "VIDocument/VIJSON.h"
#include "VIVersion.h"

/*
Visindigo Package File Structure (for user)

All the Visindigo packages are stored in the package folder, no matter it is a soft package or
built-in package. The folder for each built-in package will be created automatically when the
package is loaded, and the name of the folder is the same as the package name. The folder for
each soft package is created by the user, and the name of the folder is arbitrary.
Visindigo uses the packageMeta.json file to describe the package meta information, so the folder name
for soft package is not important, but the package name in the packageMeta.json file must be the same
as the one that compiled into the package dll file. That is to say, when you create a soft package,
you need to provide the packageMeta.json used during development as-is.
- package
	- egPackage
		- resource
		- packageMeta.json # (if dll package）
		- 1.dll # (if dll package)
		- 2.dll # (if dll package)
		- ...

Visindigo Package File Structure (for developer)
- project
	- egPackage
		- resource
			- packageMeta.json
		- cpp
			- cpp files
		- h files
*/

/*
Visindigo Package Meta Json Structure
* NOTICE: EntryPoint is not required for built-in packages, but it is required for soft packages.
* NOTICE: While the built-in packages can be loaded without 'Dependence' fieid, it is highly
* recommended to provide the 'Dependence' field for built-in packages, so that the package
* can check the version of the dependence packages.
{
	"Name": "VICore",
	"UniqueName": "cn.yxgeneral.weavestudio.visindigo.core",
	"Version": "1.2.0",
	"Author": ["Tsing Yayin"],
	"Description": "VICore",
	"License": "GPLv3",
	"URL": "",
	"EntryPoint": "",
	"Dependence":[],
	"Language": {
		"Default": "zh_SC",
		"Support": ["zh_SC", "en_US"]
	}
}
*/
#define LOAD_PACKAGE(pack_name) VICoreFramework::getCoreInstance()->loadPackage(new pack_name());
using VIPackageUniqueName = QString;

class VIPackage;
class VICoreFramework;
class VIDllPackageContainer;

struct VIPackageDependency {
	VIPackageUniqueName UniqueName;
	VIVersion Version;
	QString PackageUrl;
	def_init VIPackageDependency(const VIPackageUniqueName& name, const VIVersion& version, const QString& url = "") {
		UniqueName = name;
		Version = version;
		PackageUrl = url;
	}
};
using VIPackageDependencyMap = QMap<VIPackageUniqueName, VIPackageDependency>;

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
	_Protected QString PackageName;
	_Protected QString PackageRootPath;
	VI_ProtectedProperty(VIPackageUniqueName, UniqueName); // recommend org.orgname.project.package, eg. cn.yxgeneral.visindigo.core
	VI_ProtectedProperty(VIVersion, PackageVersion);
	VI_ProtectedProperty(QStringList, Author);
	VI_ProtectedProperty(QString, Description);
	VI_ProtectedProperty(QString, License);
	VI_ProtectedProperty(QString, URL);
	_Protected VIPackageDependencyMap PackageDependencies;
	_Protected VIDocument::VIJSON* PackageConfig;
	_Protected VIDocument::VIJSON* PackageMeta;
	_Protected VITranslationSubHost* TranslationPackageHost;
	_Public def_init VIPackageMeta();
	_Public bool initFromMetaJson();
	_Public void setPackageName(const QString& name);
	_Public inline QString getPackageName() {
		return PackageName;
	}
	_Public QString getPackageRootPath();
	_Public void call(const QString& funcName) {
		QMetaObject::invokeMethod(this, funcName.toLocal8Bit().data(), Qt::QueuedConnection);
	}
	_Public inline QString getPackageInternalPath() {
		return ":/package/" + PackageName;
	}
	_Public QString TR(const QString& key);
	_Public void addTranslationFileName(Visindigo::Language langType, const QString& filename, bool inRC = false);
	_Public void setDefaultLanguage(Visindigo::Language langType);
	_Public void initTranslation();
	_Public void addTranslatableObject(VITranslatableObject* obj);
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

using __VisindigoDllMain= VIPackage* (*)(void);

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
