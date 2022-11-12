#pragma once
#include <QtQml>
#include "VIJSGlobal.h"
#include "../VIUI/MRW/GUI2D/VI2DGUI.h"
#include "../VIUI/MRW/VIGUI2D.h"
namespace JsVI {
	class TextLabel :public QObject
	{
		Q_OBJECT
	public:
		VITextLabel* GUILabel;
	signals:
		void newTextLabel(VITextLabel**);
		void SsetText(QString, int, int, bool);
	public:
		TextLabel(QObject* parent, VIGUI2DWidget* gui) :QObject(parent) {
			connect(this, SIGNAL(newTextLabel(VITextLabel**)), gui, SLOT(newVITextLabel(VITextLabel**)), Qt::BlockingQueuedConnection);
			emit newTextLabel(&GUILabel);
			connect(this, SIGNAL(SsetText(QString, int, int, bool)), GUILabel, SLOT(setTextAni(QString, int, int, bool)), Qt::BlockingQueuedConnection);
		}
	public slots:
		void setText(QString str, int mspt = 100, int msw = 1500, bool waitForAnimation = true) {
			emit SsetText(str, mspt, msw, waitForAnimation);
			if (waitForAnimation) { VIJSHostWait; }
		}
	};
	class VIGUI2D :public QObject
	{
		Q_OBJECT
	public:
		VIGUI2DWidget* GUI;
		QJSEngine* Engine;
		VIGUI2D(QObject* parent, VIGUI2DWidget* gui, QJSEngine* engine) :QObject(parent) {
			GUI = gui;
			Engine = engine;
		}
	public slots:
		QJSValue newVIText() {
			 return Engine->newQObject(new TextLabel(this, GUI));
		}
	};

}