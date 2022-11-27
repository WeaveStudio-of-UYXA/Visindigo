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
#define SSDEF_SA_VOID(funcName) SSDEF(funcName){ emit S##funcName();}
#define JsVI_BIND_SAME(funcName, Target, ...) BIND(this, SIGNAL(S##funcName(__VA_ARGS__)), Target, SLOT(funcName(__VA_ARGS__)));
#define JsVI_BIND_SAME_VOID(funcName, Target) JsVI_BIND_SAME(funcName, Target);
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
			BIND(this, SIGNAL(Sresize(float, float)), GUIBaseLabel, SLOT(resizePercent(float, float)));
			BIND(this, SIGNAL(Smove(float, float)), GUIBaseLabel, SLOT(movePercent(float, float)));
			JsVI_BIND_SAME(resizeWidthAndRatio, GUIBaseLabel, float, float);
			JsVI_BIND_SAME(resizeHeightAndRatio, GUIBaseLabel, float, float);
			JsVI_BIND_SAME(setOpacityAni, GUIBaseLabel, float, float, int, bool);
			JsVI_BIND_SAME(setAlignment, GUIBaseLabel, Qt::AlignmentFlag);
			JsVI_BIND_SAME(setStyleSheet, GUIBaseLabel, QString);
			JsVI_BIND_SAME(setOpacity, GUIBaseLabel, float);
			JsVI_BIND_SAME_VOID(raise, GUIBaseLabel);
			JsVI_BIND_SAME_VOID(show, GUIBaseLabel);
			JsVI_BIND_SAME_VOID(hide, GUIBaseLabel);
		}
		SSDEF(setOpacityAni, float start, float end, int ms, bool wait = false) {
			emit SsetOpacityAni(start, end, ms, wait);
			if (wait) { VIJSHostWait; }
		}
		SSDEF(setOpacity, float op) {
			emit SsetOpacity(op);
		}
		SSDEF(setGeometry, float xp, float yp, float wp, float hp) {
			emit SsetGeometry(xp, yp, wp, hp);
		}
		void setAlignment(QString align) {
			if (align == "C" || align == "M") {
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
		SSDEF(move, float px, float py) {
			emit Smove(px, py);
		}
		SSDEF(resize, float pw, float ph) {
			emit Sresize(pw, ph);
		}
		SSDEF(resizeWidthAndRatio, float pw, float wToh) {
			emit SresizeWidthAndRatio(pw, wToh);
		}
		SSDEF(resizeHeightAndRatio, float ph, float hTow) {
			emit SresizeHeightAndRatio(ph, hTow);
		}
		SSDEF_SA_VOID(raise);
		SSDEF_SA_VOID(show);
		SSDEF_SA_VOID(hide);
	};
}
