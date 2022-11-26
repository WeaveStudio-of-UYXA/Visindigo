#pragma once
#include <QtQml>
#include <QtCore>
#include "VIJSGlobal.h"
#include "JsVIGUI2D.h"
#include "JsVISystem.h"
#include "VIUI/MRW/VIGUI2D.h"
#undef VIJSHostWait
class VIJSHost : public QObject
{
	Q_OBJECT
signals:
	void initJSEngine(QJSEngine*);
	void boot(QString);
public:
	QJSEngine* Engine;
	JsVI::VIGUI2D* VIGUI2D;
	JsVI::VISystem* VISystem;
	VIJSHost(VIGUI2DWidget* gui) {
		Engine = new QJSEngine(this);
		VIGUI2D = new JsVI::VIGUI2D(this, gui, Engine);
		VISystem = new JsVI::VISystem(this);
		connect(this, SIGNAL(boot(QString)), this, SLOT(eval(QString)));
	}
public slots:
	void eval(QString filename) {
		emit initJSEngine(Engine);
		initEngine();
		VIJSGlobal::VIJSMutex.lock();
		int RTN = 0;
		qDebug() << filename;
		QFileInfo fileInfo(filename);
		VIJSGlobal::Path = fileInfo.absolutePath();
		qDebug() << VIJSGlobal::Path;
		QJSValue Main = Engine->importModule(filename);
		QJSValue MainFuncation = Main.property("main");
		QJSValue result = MainFuncation.call();
		if (result.isError()) {
			qDebug() << "Uncaught exception at line" << result.property("lineNumber").toNumber() << ":" << result.toString();
			RTN = 1;
		}
		VIJSGlobal::VIJSMutex.unlock();
	}
	void initEngine() {
		QJSValue VI2D = Engine->newQObject(VIGUI2D);
		Engine->globalObject().setProperty("VIGUI", VI2D);
		QJSValue VITextLabel = Engine->newQMetaObject(&JsVI::TextLabel::staticMetaObject);
		VI2D.setProperty("VITextLabel", VITextLabel);
		QJSValue VISys = Engine->newQObject(VISystem);
		Engine->globalObject().setProperty("VISystem", VISys);
	}
};