﻿#pragma once
#include "JsVIGUI2DBase.h"
#include "VIUI/MRW/VIGUI2D.h"

namespace JsVI {
	class TextLabel :public GUI2DLabel
	{
		Q_OBJECT
			JsVI_INVOKE(VITextLabel)
	signals:
		void StextNonlinerProgress(VIMath::VI2DMatrix mat);
		
	public:
		TextLabel(JsVIGUI_PARA) {
			JsVI_NewFrom(VITextLabel);
			JsVI_INIT;
			BIND(this, SIGNAL(StextNonlinerProgress(VIMath::VI2DMatrix)), JsVIGUI, SLOT(textNonlinerProgress(VIMath::VI2DMatrix)));
			JsVI_BIND_SAME(setTextAni, JsVIGUI, QString, int, int, bool);
			JsVI_BIND_SAME(continueTextAni, JsVIGUI, QString, int, int, bool);
			JsVI_BIND_SAME(setText, JsVIGUI, QString);
			/*for (int i = this->metaObject()->methodCount(); i > 0; i--) {
				QMetaMethod method = this->metaObject()->method(i);
				qDebug() << method.typeName() << method.methodSignature();
			}*/
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
		SSDEF(setTextAni, QString str, int mspt = 100, int msw = 1500, bool wait = true) {
			emit SsetTextAni(str, mspt, msw, wait);
			JsVI_WAIT(wait);
		}
		SSDEF(continueTextAni, QString str, int mspt = 100, int msw = 1500, bool wait = true) {
			emit ScontinueTextAni(str, mspt, msw, wait);
			JsVI_WAIT(wait);
		}
		SSDEF(setText, QString str) {
			emit SsetText(str);
		}
		
	};

	class PictureLabel :public GUI2DLabel
	{
		Q_OBJECT
			JsVI_INVOKE(VIPictureLabel)
	signals:
		void SsetImage(QString);
		void SfillColor(int, int, int, int);
	public:
		PictureLabel(JsVIGUI_PARA) {
			JsVI_NewFrom(VIPictureLabel);
			JsVI_INIT;
			BIND(this, SIGNAL(SsetImage(QString)), JsVIGUI, SLOT(setImage(QString)));
			BIND(this, SIGNAL(SfillColor(int, int, int, int)), JsVIGUI, SLOT(fillColor(int, int, int, int)));
		}
	public slots:
		void setPicture(QString path) {
			emit SsetImage(VIJSGlobal::getAbsolutePathOf(path));
		}
		void fillColor(int r, int g, int b, int a = 255) {
			emit SfillColor(r, g, b, a);
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
	public:
		VIGUI2DWidget* GUI;
		QJSEngine* Engine;
		VIGUI2D(QObject* parent, VIGUI2DWidget* gui, QJSEngine* engine) :QObject(parent) {
			GUI = gui;
			Engine = engine;
		}
	public slots:
		SSDEF_SA_VOID(enableGUIFrame);
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
		SSDEF_SA_VOID(showFullScreen);
	};
}