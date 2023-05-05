#pragma once
#include "../../Visindigo/VICore/VIPackage.h"
#include "../../VIUI/MRW/VisindigoRuntime.h"

class YSPMainPack :public VIPackage
{
	Q_OBJECT;
	_Public def_init YSPMainPack(QObject* parent = nullptr) {
		doQRegisterMetaType();
		VIRuntimeWindow* w = new VIRuntimeWindow();
#if VI_WINDOW == VI_WINDOW_SYS
		w->showFullScreen();
#elif VI_WINDOW == VI_NO_WINDOW
		w->show();
#endif
	};
	_Private void doQRegisterMetaType() {
		qRegisterMetaType<VIMath::VI2DMatrix>("VIMath::VI2DMatrix");
		qRegisterMetaType<VIMath::VIVector2>("VIMath::VIVector2");
		qRegisterMetaType<VIMath::VIMatrix>("VIMath::VIMatrix");
		qRegisterMetaType<QList<QList<int>>>("QList<QList<int>>");
	};
};