#pragma once
#include <QtCore>
#include <QtWidgets>
#include "macro/VIMarco.h"
#include "VIPackage.h"
class VIFramework;
class private_VIFramework :public QObject
{
	friend class VIFramework;
	_Public QList<VIPackage*> PackageList = {};
	_Public int ReturnCode = 0;
};
class VIFramework :public QApplication
{
	Q_OBJECT;
	_Private private_VIFramework* Data;
	_Public static VIFramework* Instance;
	_Public def_init VIFramework(int& argc, char** argv) :QApplication(argc, argv) {
		Data = new private_VIFramework();
		VIFramework::Instance = this;
	};
	_Public void start() { gBEHAVIOR->start(); mBEHAVIOR->start(); Data->ReturnCode = this->exec(); };
	_Public int getReturnCode() { return Data->ReturnCode; };
	_Public bool loadPackage(VIPackage* package) { 
		Data->PackageList.append(package); 
		package->active();
		return true; 
	};
};