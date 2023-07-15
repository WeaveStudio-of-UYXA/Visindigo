#pragma once
#include "../VICore/VICoreFramework.h"
#include "VIStyleSheet.h"

class VIFramework :public VICoreFramework
{
	Q_OBJECT;
	VI_OBJECT;
	_Private static VIFramework* Instance;
	VI_PrivateProperty(VIPaletteGroup*, PaletteGroup);
	_Public def_init VIFramework(int& argc, char** argv);
	_Public void init();
	_Public void start();
	_Public static VIFramework* getInstance();
};

#define VIFrame VIFramework::getInstance()