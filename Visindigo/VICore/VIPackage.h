#pragma once
#include <QtCore>
#include "VIObject.h"
#include "VIBehavior.h"

#define LOAD_PACKAGE(pack_name) VICoreFramework::getCoreInstance()->loadPackage(new pack_name());
class VIPackage;
class VICoreFramework;

class VIPackageInfo :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_MUST_INHERIT(VIPackageInfo);
	friend class VICoreFramework;
	friend class VIPackage;
	VI_Singleton(VIPackageInfo);
	VI_ProtectedProperty(QString, PackageName);
	VI_ProtectedProperty(unsigned int, PackageVersionMajor);
	VI_ProtectedProperty(unsigned int, PackageVersionMinor);
	VI_ProtectedProperty(unsigned int, PackageVersionPatch);
	VI_ProtectedProperty(QStringList, Author);
	VI_ProtectedProperty(QString, Description);
	VI_ProtectedProperty(QString, License);
	VI_ProtectedProperty(QString, URL);
	VI_ProtectedProperty(QString, Organization);
	VI_ProtectedProperty(QString, OrganizationDomain);
	_Public def_init VIPackageInfo(){
		this->setPackageName("UnnamedVIPackage");
		this->setPackageVersionMajor(0);
		this->setPackageVersionMinor(0);
		this->setPackageVersionPatch(0);
		this->setAuthor(QStringList());
		this->setDescription("");
		this->setLicense("");
		this->setURL("");
		this->setOrganization("");
		this->setOrganizationDomain("");
		_instance = this;
	}
	_Public QString getPackageVersion() {
		return QString("%1.%2.%3").arg(PackageVersionMajor).arg(PackageVersionMinor).arg(PackageVersionPatch);
	}
};

class VIPackage :public VIBasicBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIFramework;
	VI_Property(VIPackageInfo*, PackageInfo);
	_Public def_init VIPackage(){
		this->setObjectName("UnnamedVIPackage");
	};
	_Public virtual void onActive() HalfVirtual;
	_Public virtual void onSubside() HalfVirtual;
	_Public virtual void onTick() HalfVirtual;
	_Public virtual void onEvent(QEvent* e) HalfVirtual;
	
};