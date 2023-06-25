#pragma once
#include <QtCore>
#include "VIObject.h"
#include "VIBehavior.h"

#define LOAD_PACKAGE(pack_name) VIFramework::getInstance()->loadPackage(new pack_name());
class VIPackage;
class VIFramework;

class VIPackageInfo :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIFramework;
	friend class VIPackage;
	_Private static VIPackageInfo* Instance;
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
	_Public def_init VIPackageInfo(VIObject* parent = VI_NULLPTR) :VIObject(parent) {
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
		Instance = this;
	}
	_Public QString getPackageVersion() {
		return QString("%1.%2.%3").arg(PackageVersionMajor).arg(PackageVersionMinor).arg(PackageVersionPatch);
	}
	_Public static VIPackageInfo* getInstance(){return Instance;}
};

class VIPackage :public VIBasicBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIFramework;
	VI_Property(VIPackageInfo*, PackageInfo);
	_Public def_init VIPackage(QObject* parent = VI_NULLPTR) :VIBasicBehavior(parent) {
		this->setObjectName("UnnamedVIPackage");
	};
	_Public virtual void onActive() HalfVirtual;
	_Public virtual void onSubside() HalfVirtual;
	_Public virtual void onTick() HalfVirtual;
	_Public virtual void onEvent(QEvent* e) HalfVirtual;
	
};