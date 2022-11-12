#pragma once
#include <QtQml>
#include <QtCore>
#include "JSVIAPI.h"
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
	JSVIAPI::System::Host* SystrmHost;
	VIJSHost(QObject* parent = Q_NULLPTR):QObject(parent) {
		Engine = new QJSEngine(this);
		GUIHost = new JSVIAPI::GUI::Host(this);
		SystrmHost = new JSVIAPI::System::Host(this);
		connect(this, SIGNAL(boot(QString)), this, SLOT(eval(QString)));
	}
public slots:
	void eval(QString filename) {
		emit initJSEngine(Engine);
		initEngine();
		VIJSMutex.lock();
		int RTN = 0;
		qDebug() << "EVAL";
		qDebug() << filename;
		QJSValue Main = Engine->importModule(filename);
		QJSValue MainFuncation = Main.property("main");
		QJSValue result = MainFuncation.call();
		if (result.isError()) {
			qDebug() << "Uncaught exception at line" << result.property("lineNumber").toNumber() << ":" << result.toString();
			RTN =  1;
		}
		VIJSMutex.unlock();
	}
	void initEngine() {
		QJSValue VI2D = Engine->newQObject(GUIHost);
		Engine->globalObject().setProperty("VIGUI", VI2D);
		QJSValue VISys = Engine->newQObject(SystrmHost);
		Engine->globalObject().setProperty("VISystem", VISys);
		
	}
};