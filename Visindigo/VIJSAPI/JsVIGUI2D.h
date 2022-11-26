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
		void SsetAlignment(Qt::AlignmentFlag);
	public:
		TextLabel(JsVIGUI_PARA) {
			JsVI_NewFrom(VITextLabel);
			JsVI_INIT;
			BIND(this, SIGNAL(StextNonlinerProgress(VIMath::VI2DMatrix)), JsVIGUI, SLOT(textNonlinerProgress(VIMath::VI2DMatrix)));
			BIND(this, SIGNAL(SsetAlignment(Qt::AlignmentFlag)), JsVIGUI, SLOT(setAlign(Qt::AlignmentFlag)));
			JsVI_AniBIND(setText, QString, int, int, bool);
			JsVI_AniBIND(continueText, QString, int, int, bool);
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
		SSDEF(setText, QString str, int mspt = 100, int msw = 1500, bool wait = true) {
			emit SsetText(str, mspt, msw, wait);
			JsVI_WAIT(wait);
		}
		SSDEF(continueText, QString str, int mspt = 100, int msw = 1500, bool wait = true) {
			emit ScontinueText(str, mspt, msw, wait);
			JsVI_WAIT(wait);
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

	class PictureLabel :public GUI2DLabel
	{
		Q_OBJECT
			JsVI_INVOKE(VIPictureLabel)
	signals:
		void SsetImage(QString);
	public:
		PictureLabel(JsVIGUI_PARA) {
			JsVI_NewFrom(VIPictureLabel);
			JsVI_INIT;
			BIND(this, SIGNAL(SsetImage(QString)), JsVIGUI, SLOT(setImage(QString)));
		}
	public slots:
		void setPicture(QString path) {
			emit SsetImage(VIJSGlobal::getAbsolutePathOf(path));
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
		QJSValue newVIPicture() {
			return Engine->newQObject(new PictureLabel(this, GUI));
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