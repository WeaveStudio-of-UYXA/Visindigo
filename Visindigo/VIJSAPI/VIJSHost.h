#pragma once
#include <QtScript>
#include <QtCore>
#include "JSVIAPI.h"
#undef VIJSHostWait
class VIJSHost : public QObject
{
	Q_OBJECT
signals:
	void initJSEngine(QScriptEngine*);
	void boot(QString);
public:
	QScriptEngine* Engine;
	JSVIAPI::GUI::Host* GUIHost;
	VIJSHost(QObject* parent = Q_NULLPTR):QObject(parent) {
		Engine = new QScriptEngine(this);
		GUIHost = new JSVIAPI::GUI::Host(this);
		connect(this, SIGNAL(boot(QString)), this, SLOT(eval(QString)));
	}
public slots:
	void eval(QString code) {
		emit initJSEngine(Engine);
		initEngine();
		VIJSMutex.lock();
		int RTN = 0;
		qDebug() << "EVAL";
		QScriptValue result = Engine->evaluate(code+"main();");
		if (result.isError()) {
			qDebug() << "Uncaught exception at line" << result.property("lineNumber").toInt32() << ":" << result.toString();
			RTN =  1;
		}
		VIJSMutex.unlock();
	}
	void initEngine() {
		QScriptValue VI2D = Engine->newQObject(GUIHost);
		Engine->globalObject().setProperty("GUI", VI2D);
		
	}
};