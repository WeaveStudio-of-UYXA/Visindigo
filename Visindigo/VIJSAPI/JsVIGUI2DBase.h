#pragma once
#include "VIUI/MRW/GUI2D/VI2DGUIBase.h"
#include "VIJSGlobal.h"
#define SSDEF(funcName,...) Q_SIGNALS: void S##funcName(__VA_ARGS__);public Q_SLOTS:void funcName(__VA_ARGS__)
#define JsVI_INVOKE(VIGUI) public: VIGUI* GUILabel;
#define JsVIGUI GUILabel
namespace JsVI {
	class GUI2DLabel :public QObject
	{
		Q_OBJECT
	public:
		VI2DGUILabel* GUIBaseLabel;
	public:
		void __init__(QObject* parent, VI2DGUILabel* GUIBase) {
			this->setParent(parent);
			GUIBaseLabel = GUIBase;
			BIND(this, SIGNAL(SsetGeometry(float, float, float, float)), GUIBaseLabel, SLOT(setGeometryPercent(float, float, float, float)));
			BIND(this, SIGNAL(SsetOpacity(float, float, int, bool)), GUIBaseLabel, SLOT(setOpacityAni(float, float, int, bool)));
		}
		SSDEF(setOpacity, float start, float end, int ms, bool wait = false) {
			emit SsetOpacity(start, end, ms, wait);
			if (wait) { VIJSHostWait; }
		}
		SSDEF(setGeometry, float xp, float yp, float wp, float hp) {
			emit SsetGeometry(xp, yp, wp, hp);
		}
	};
}
