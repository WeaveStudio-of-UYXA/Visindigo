#pragma once
#include "VIUI/MRW/GUI2D/VI2DGUIBase.h"
#include "VIJSGlobal.h"
#include "JsVIBase.h"
#define SSDEF(funcName,...) Q_SIGNALS: void S##funcName(__VA_ARGS__);public Q_SLOTS:void funcName(__VA_ARGS__)
#define JsVIGUI GUILabel
#define JsVIGUI_PARA QObject* parent, VIGUI2DWidget* gui
#define JsVI_INVOKE(VIGUI) public: VIGUI* GUILabel; Q_SIGNALS: void newGUILabel(VIGUI**);
#define JsVI_NewFrom(type) BIND(this, SIGNAL(newGUILabel(type**)), gui, SLOT(new##type(type**))); emit newGUILabel(&JsVIGUI);
#define JsVI_INIT __init__(parent, (VI2DGUILabel*)JsVIGUI);
#define JsVI_WAIT(para) if (para) { VIJSHostWait; }
#define JsVI_AniBIND(func, ...) BIND(this, SIGNAL(S##func(__VA_ARGS__)), JsVIGUI, SLOT(func##Ani(__VA_ARGS__)));
namespace JsVI {
	class GUI2DLabel :public QObject
	{
		Q_OBJECT
	signals:
		void SsetAlignment(Qt::AlignmentFlag);
	public:
		VI2DGUILabel* GUIBaseLabel;
	public:
		void __init__(QObject* parent, VI2DGUILabel* GUIBase) {
			this->setParent(parent);
			GUIBaseLabel = GUIBase;
			BIND(this, SIGNAL(SsetGeometry(float, float, float, float)), GUIBaseLabel, SLOT(setGeometryPercent(float, float, float, float)));
			BIND(this, SIGNAL(SsetOpacity(float, float, int, bool)), GUIBaseLabel, SLOT(setOpacityAni(float, float, int, bool)));
			BIND(this, SIGNAL(SsetAlignment(Qt::AlignmentFlag)), GUIBaseLabel, SLOT(setAlignment(Qt::AlignmentFlag)));
			BIND(this, SIGNAL(SsetStyleSheet(QString)), GUIBaseLabel, SLOT(setStyleSheet(QString)));
		}
		SSDEF(setOpacity, float start, float end, int ms, bool wait = false) {
			emit SsetOpacity(start, end, ms, wait);
			if (wait) { VIJSHostWait; }
		}
		SSDEF(setGeometry, float xp, float yp, float wp, float hp) {
			emit SsetGeometry(xp, yp, wp, hp);
		}
		void setAlignment(QString align) {
			if (align == "C") {
				emit SsetAlignment(Qt::AlignCenter);
			}
			else if (align == "L") {
				emit SsetAlignment(Qt::AlignLeft);
			}
			else if (align == "R") {
				emit SsetAlignment(Qt::AlignRight);
			}
			else {
				emit SsetAlignment(Qt::AlignLeft);
			}
		}
		SSDEF(setStyleSheet, QString style) {
			emit SsetStyleSheet(style);
		}
	};
}
