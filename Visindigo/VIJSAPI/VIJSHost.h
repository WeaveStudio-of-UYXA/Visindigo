#pragma once
#include <QtQml>
#include <QtCore>
#include "JSVIAPI.h"
#include "VIJSGlobal.h"
#include "JsVIGUI2D.h"
#include "../VIUI/MRW/VIGUI2D.h"
#undef VIJSHostWait
class VIJSHost : public QObject
{
	Q_OBJECT
signals:
	void initJSEngine(QJSEngine*);
	void boot(QString);
public:
	QJSEngine* Engine;
	JSVIAPI::GUI::Host* GUIHost;
	JSVIAPI::System::Host* SystemHost;
	JsVI::VIGUI2D* VIGUI2D;
	VIJSHost(VIGUI2DWidget* gui){
		Engine = new QJSEngine(this);
		GUIHost = new JSVIAPI::GUI::Host(this);
		SystemHost = new JSVIAPI::System::Host(this);
		VIGUI2D = new JsVI::VIGUI2D(this, gui, Engine);
		connect(this, SIGNAL(boot(QString)), this, SLOT(eval(QString)));
	}
public slots:
	void eval(QString filename) {
		emit initJSEngine(Engine);
		initEngine();
		VIJSGlobal::VIJSMutex.lock();
		int RTN = 0;
		qDebug() << filename;
		QJSValue Main = Engine->importModule(filename);
		QJSValue MainFuncation = Main.property("main");
		QJSValue result = MainFuncation.call();
		if (result.isError()) {
			qDebug() << "Uncaught exception at line" << result.property("lineNumber").toNumber() << ":" << result.toString();
			RTN =  1;
		}
		VIJSGlobal::VIJSMutex.unlock();
	}
	void initEngine() {
		QJSValue VI2D = Engine->newQObject(VIGUI2D);
		Engine->globalObject().setProperty("VIGUI", VI2D);
		QJSValue VISys = Engine->newQObject(SystemHost);
		Engine->globalObject().setProperty("VISystem", VISys);
		QJSValue VITextLabel = Engine->newQMetaObject(&JsVI::TextLabel::staticMetaObject);
		Engine->globalObject().setProperty("VITextLabel", VITextLabel);
	}
};