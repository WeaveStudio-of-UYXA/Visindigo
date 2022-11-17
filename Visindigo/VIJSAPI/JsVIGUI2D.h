#pragma once
#include <QtQml>
#include "VIJSGlobal.h"
#include "VIUI/MRW/GUI2D/VI2DGUI.h"
#include "VIUI/MRW/VIGUI2D.h"
#include "Global.h"

namespace JsVI {
	class TextLabel :public QObject
	{
		Q_OBJECT
	public:
		VITextLabel* GUILabel;
	signals:
		void StextNonlinerProgress(VIMath::VI2DMatrix mat);
		void newTextLabel(VITextLabel**);
		void SsetText(QString, int, int, bool);
		void ScontinueText(QString, int, int, bool);
		void SsetAlignment(Qt::AlignmentFlag);
		void SsetGeometry(float, float, float, float);
		void SsetOpacity(float, float, int, bool);
	public:
		TextLabel(QObject* parent, VIGUI2DWidget* gui) :QObject(parent) {
			BIND(this, SIGNAL(newTextLabel(VITextLabel**)), gui, SLOT(newVITextLabel(VITextLabel**)));
			emit newTextLabel(&GUILabel);
			BIND(this, SIGNAL(StextNonlinerProgress(VIMath::VI2DMatrix)), GUILabel, SLOT(textNonlinerProgress(VIMath::VI2DMatrix)));
			BIND(this, SIGNAL(SsetText(QString, int, int, bool)), GUILabel, SLOT(setTextAni(QString, int, int, bool)));
			BIND(this, SIGNAL(ScontinueText(QString, int, int, bool)), GUILabel, SLOT(continueTextAni(QString, int, int, bool)));
			BIND(this, SIGNAL(SsetAlignment(Qt::AlignmentFlag)), GUILabel, SLOT(setAlign(Qt::AlignmentFlag)));
			BIND(this, SIGNAL(SsetGeometry(float, float, float, float)), GUILabel, SLOT(setGeometryPercent(float, float, float, float)));
			BIND(this, SIGNAL(SsetOpacity(float, float, int, bool)), GUILabel, SLOT(setOpacityAni(float, float, int, bool)));
		}
	public slots:
		void textNonlinerProgress(QList<QList<float>> mat) {
			VIMath::VIVector2 vec;
			VIMath::VI2DMatrix rtn;
			for (auto i = mat.begin(); i != mat.end(); i++) {
				vec = { (*i).at(0),(*i).at(1) };
				rtn.append(vec);
			}
			emit StextNonlinerProgress(rtn);
		}
		void setText(QString str, int mspt = 100, int msw = 1500, bool waitForAnimation = true) {
			emit SsetText(str, mspt, msw, waitForAnimation);
			if (waitForAnimation) { VIJSHostWait; }
		}
		void continueText(QString str, int mspt = 100, int msw = 1500, bool wFA = true) {
			emit ScontinueText(str, mspt, msw, wFA);
			if (wFA) { VIJSHostWait; }
		}
		void setOpacity(float start, float end, int ms, bool wait = false) {
			emit SsetOpacity(start, end, ms, wait);
			if (wait) { VIJSHostWait; }
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
			else{
				emit SsetAlignment(Qt::AlignLeft);
			}
		}
		void setGeometry(float xp, float yp, float wp, float hp) {
			emit SsetGeometry(xp, yp, wp, hp);
		}
	};
	class VIGUI2D :public QObject
	{
		Q_OBJECT
	signals:
		void SsetWindowTitle(QString);
		void Sresize(int, int);
		void SsetGeometry(int, int, int, int);
		void SsetStyleSheet(QString);
		void SshowFullScreen();
		void SenableGUIFrame();
	public:
		VIGUI2DWidget* GUI;
		QJSEngine* Engine;
		VIGUI2D(QObject* parent, VIGUI2DWidget* gui, QJSEngine* engine) :QObject(parent) {
			GUI = gui;
			Engine = engine;
		}
	public slots:
		void enableGUIFrame() {
			emit SenableGUIFrame();
		}
		QJSValue newVIText() {
			return Engine->newQObject(new TextLabel(this, GUI));
		}
		void resize(int w, int h) {
#if DEPLOY == WINDOWS_DEPLOY
			emit Sresize(w, h);
#endif
		}
		void setGeometry(int x, int y, int w, int h) {
#if DEPLOY == WINDOWS_DEPLOY
			emit SsetGeometry(x, y, w, h);
#endif
		}
		void setStyleSheet(QString style) {
			emit SsetStyleSheet(style);
		}
		void setWindowTitle(QString title) {
			emit SsetWindowTitle(title);
		}
		void showFullScreen() {
			emit SshowFullScreen();
		}
	};
}