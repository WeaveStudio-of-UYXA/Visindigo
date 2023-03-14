#pragma once
#include <QtCore>
#include <QtWidgets>
#include "../../../CommonEdit/CECore/CEMacro.h"
#include "VIPackage.h"

#define INIT_FRAMEWORK(argc, argv) VIFramework VIFrame(argc, argv);
class VIFramework :public QApplication
{
	Q_OBJECT;
	_Public static VIFramework* Instance;
	_Public QVector<VIPackage*> PackageList;
	_Public def_init VIFramework(int& argc, char** argv) :QApplication(argc, argv) {};
	_Public bool loadPackage(VIPackage* package);
};