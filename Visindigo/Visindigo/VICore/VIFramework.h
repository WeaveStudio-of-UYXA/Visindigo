#pragma once
#include <QtCore>
#include <QtWidgets>
#include "private/VIMacro.h"
#include "VIPackage.h"

#define FrameBehaviorHost VIFramework::getBehaviorHostInstance()
class VIFramework;
class private_VIFramework :public QObject
{
	Q_OBJECT;
	friend class VIFramework;
	_Public QList<VIPackage*> PackageList = {};
	_Public int ReturnCode = 0;
};
class VIFramework :public QObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private private_VIFramework* Data;
	_Private static VIFramework* Instance;
	_Private static VIBehaviorHost* BehaviorHost;
	_Private QApplication* App;
	_Public def_init VIFramework(int& argc, char** argv){
		App = new QApplication(argc, argv);
		Data = new private_VIFramework();
		VIFramework::Instance = this;
		BehaviorHost = new VIBehaviorHost(this);
	};
	_Public static VIBehaviorHost* getBehaviorHostInstance() {
		if (BehaviorHost == nullptr) {
			qDebug().noquote() << "Visindigo requires a VIFramework instance to initialize various program components. \
Before loading your package, you must first create a new VIFramework instance.\nThe program will exit.\n";
			std::exit(-1);
		}
		return BehaviorHost;
	};
	_Public void start() {
		//gBEHAVIOR->start(); 
		//mBEHAVIOR->start();
		
		BehaviorHost->start();
		Data->ReturnCode = App->exec();
	};
	_Public static VIFramework* getInstance() {
		if (VIFramework::Instance == nullptr) {
			qDebug().noquote() << "Visindigo requires a VIFramework instance to initialize various program components. \
Before loading your package, you must first create a new VIFramework instance.\nThe program will exit.\n";
			std::exit(-1);
		}
		return VIFramework::Instance;
	};
	_Public int getReturnCode() { return Data->ReturnCode; };
	_Public bool loadPackage(VIPackage* package) {
		package->Framework = this;
		Data->PackageList.append(package);
		package->active();
		return true;
	};
};