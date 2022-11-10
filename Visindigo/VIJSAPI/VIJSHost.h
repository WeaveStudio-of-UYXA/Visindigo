#pragma once
#include <QtScript>
#include <QtCore>

class VIJSHost : public QObject
{
	Q_OBJECT
signals:
	void initJSEngine(QScriptEngine*);
	void boot(QString);
public:
	QScriptEngine* Engine;
	VIJSHost(QObject* parent = Q_NULLPTR):QObject(parent) {

		Engine = new QScriptEngine(this);
		connect(this, SIGNAL(boot(QString)), this, SLOT(eval(QString)));
	}
public slots:
	void eval(QString code) {
		emit initJSEngine(Engine);
		int RTN = 0;
		Engine->evaluate(code);
		QScriptValue result = Engine->evaluate("main()");
		if (result.isError()) {
			qDebug() << "Uncaught exception at line" << result.property("lineNumber").toInt32() << ":" << result.toString();
			RTN =  1;
		}
		Engine->deleteLater();
		Engine = new QScriptEngine(this);
	}
};