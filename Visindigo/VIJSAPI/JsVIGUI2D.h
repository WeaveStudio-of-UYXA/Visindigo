#pragma once
#include "JsVIGUI2DBase.h"
#include "VIUI/MRW/VIGUI2D.h"

namespace JsVI {
	class TextLabel :public GUI2DLabel
	{
		Q_OBJECT
			JsVI_INVOKE(VITextLabel)
	signals:
		void StextNonlinerProgress(VIMath::VI2DMatrix mat);
		void newTextLabel(VITextLabel**);
		void SsetAlignment(Qt::AlignmentFlag);
	public:
		TextLabel(QObject* parent, VIGUI2DWidget* gui) {
			BIND(this, SIGNAL(newTextLabel(VITextLabel**)), gui, SLOT(newVITextLabel(VITextLabel**)));
			emit newTextLabel(&JsVIGUI);
			__init__(parent, (VI2DGUILabel*)JsVIGUI);
			BIND(this, SIGNAL(StextNonlinerProgress(VIMath::VI2DMatrix)), JsVIGUI, SLOT(textNonlinerProgress(VIMath::VI2DMatrix)));
			BIND(this, SIGNAL(SsetText(QString, int, int, bool)), JsVIGUI, SLOT(setTextAni(QString, int, int, bool)));
			BIND(this, SIGNAL(ScontinueText(QString, int, int, bool)), JsVIGUI, SLOT(continueTextAni(QString, int, int, bool)));
			BIND(this, SIGNAL(SsetAlignment(Qt::AlignmentFlag)), JsVIGUI, SLOT(setAlign(Qt::AlignmentFlag)));
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
		SSDEF(setText, QString str, int mspt = 100, int msw = 1500, bool waitForAnimation = true) {
			emit SsetText(str, mspt, msw, waitForAnimation);
			if (waitForAnimation) { VIJSHostWait; }
		}
		SSDEF(continueText, QString str, int mspt = 100, int msw = 1500, bool wFA = true) {
			emit ScontinueText(str, mspt, msw, wFA);
			if (wFA) { VIJSHostWait; }
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