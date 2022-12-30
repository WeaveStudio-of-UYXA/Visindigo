#pragma once
#include "VIUI/MRW/GUI2D/VI2DGUIBase.h"
#include "VIJSGlobal.h"
#include "JsVIBase.h"
#include "macro/VIJSGlobal_m.h"

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
			JsVI_CONNECT_SAME_VOID(del, GUIBaseLabel);
			JsVI_CONNECT_SAME_VOID(hide, GUIBaseLabel);
			BIND(this, SIGNAL(Smove(float, float)), GUIBaseLabel, SLOT(movePercent(float, float)));
			JsVI_BIND_SAME(moveCenter, GUIBaseLabel, float, float);
			JsVI_CONNECT_SAME_VOID(raise, GUIBaseLabel);
			BIND(this, SIGNAL(Sresize(float, float)), GUIBaseLabel, SLOT(resizePercent(float, float)));
			JsVI_BIND_SAME(resizeWidthAndRatio, GUIBaseLabel, float, float);
			JsVI_BIND_SAME(setAlignment, GUIBaseLabel, Qt::AlignmentFlag);
			BIND(this, SIGNAL(SsetGeometry(float, float, float, float)), GUIBaseLabel, SLOT(setGeometryPercent(float, float, float, float)));
			JsVI_BIND_SAME(setOpacity, GUIBaseLabel, float);
			JsVI_BIND_SAME(setOpacityAni, GUIBaseLabel, float, float, int, bool);
			JsVI_BIND_SAME(setStyleSheet, GUIBaseLabel, QString);
			JsVI_CONNECT_SAME_VOID(show, GUIBaseLabel);
		}
		Q_INVOKABLE ~GUI2DLabel() {
		}
		SSDEF(del) {
			emit Sdel();
			this->disconnect();
			this->deleteLater();
		}
		SSDEF_SA_VOID(hide);
		SSDEF(move, float px, float py) {
			emit Smove(px, py);
		}
		SSDEF(moveCenter, float pcx, float pcy) {
			emit SmoveCenter(pcx, pcy);
		}
		SSDEF_SA_VOID(raise);
		SSDEF(resize, float pw, float ph) {
			emit Sresize(pw, ph);
		}
		SSDEF(resizeWidthAndRatio, float pw, float wToh) {
			emit SresizeWidthAndRatio(pw, wToh);
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
		SSDEF(setGeometry, float xp, float yp, float wp, float hp) {
			emit SsetGeometry(xp, yp, wp, hp);
		}
		SSDEF(setOpacityAni, float start, float end, int ms, bool wait = false) {
			emit SsetOpacityAni(start, end, ms, wait);
			if (wait) { VIJSHostWait; }
		}
		SSDEF(setOpacity, float op) {
			emit SsetOpacity(op);
		}
		SSDEF(setStyleSheet, QString style) {
			emit SsetStyleSheet(style);
		}
		SSDEF_SA_VOID(show);
	};
}
