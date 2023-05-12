#pragma once
#include "VIJSGlobal.h"
#include "JsVIGUI2D.h"
#include "JsVISystem.h"
#include "../../VIUI/MRW/VIGUI2D.h"
#include "../VICore/VIObject.h"
#undef VIJSHostWait
//这个VIJSHostWait啊，谁在VIJSHost会执行的代码里面调用我跟谁过不去。
class VIJSHost : public VIObject 
{
	Q_OBJECT;
	VI_OBJECT;
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
		consoleLog(filename);
		QFileInfo fileInfo(filename);
		VIJSGlobal::Path = fileInfo.absolutePath();
		consoleLog(VIJSGlobal::Path);
		QJSValue Main = Engine->importModule(filename);
		QJSValue YSPModule = Engine->importModule(":/Visindigo/JsVIAPI/YSP.js");
		Engine->globalObject().setProperty("SPOL", YSPModule);
		Engine->installExtensions(QJSEngine::GarbageCollectionExtension);
		QJSValue MainFuncation = Main.property("main");
		QJSValue result = MainFuncation.call();
		consoleLog(result.toString());
		if (result.isError()) {
			qDebug() << "Uncaught exception at line" << result.property("lineNumber").toNumber() << ":" << result.toString();
			RTN = 1;

		}
		Engine->collectGarbage();
		VIJSGlobal::VIJSMutex.unlock();
	}
	void initEngine() {
		QJSValue VI2D = Engine->newQObject(VIGUI2D);
		Engine->globalObject().setProperty("VIGUI", VI2D);
		QJSValue VIGUI2DLabel = Engine->newQMetaObject(&JsVI::GUI2DLabel::staticMetaObject);
		VI2D.setProperty("VIGUI2DLabel", VIGUI2DLabel);
		QJSValue VITextLabel = Engine->newQMetaObject(&JsVI::TextLabel::staticMetaObject);
		VI2D.setProperty("VITextLabel", VITextLabel);
		QJSValue VISys = Engine->newQObject(VISystem);
		Engine->globalObject().setProperty("VISystem", VISys);
	}
};