#pragma once
#include "../../VICore/VIObject.h"
#include "../../VICore/VIBehavior.h"
#include "../../VICore/VISystem.h"
#include <QtQml>
#include "VIES_System.h"
class VIECMAScripts :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QJSEngine* Engine;
	_Private QJSValue* Global;
	_Private QJSValue Main;
	_Private QJSValue MainClass;
	_Private QString UserMain;
	_Private QFileInfo UserMainFileInfo;
	_Private QMap<QString, QString> SideModules;
	_Private bool firstBoot = true;
	_Public def_init VIECMAScripts(VISuper* parent = VI_NULLPTR) :VIObject(parent) {
		Engine = new QJSEngine(this);
		Engine->installExtensions(QJSEngine::ConsoleExtension);
		Global = &(Engine->globalObject());
	};
	_Public QJSValue evals(QString code) {
		return Engine->evaluate(code);
	};
	_Public void setUserMain(QString filePath) {
		UserMainFileInfo = QFileInfo(filePath);
		UserMain = UserMainFileInfo.absoluteFilePath();
		consoleLog(UserMain);
	};
	_Public void setUserMain(QFileInfo fileInfo) {
		UserMainFileInfo = fileInfo;
		UserMain = UserMainFileInfo.absoluteFilePath();
	};
	_Public void importSideModule(QString moduleName, QString filePath) {
		if (SideModules.contains(moduleName)) {
			throw "Module name already exists.";
		}
		else {
			SideModules.insert(moduleName, filePath);
		}
	}
	_Public QJSValue boot(QString entryPoint = "main") {
		if (firstBoot) {
			firstBoot = false;
			
			QJSValue System = Engine->newQObject(new VIES_System(this));
			Engine->globalObject().setProperty("System", System);
			QJSValue VIESBase = Engine->importModule(":/Visindigo/JsVIAPI/VIESObject.js");
			consoleLog("Uncaught exception at line"+QString::number(VIESBase.property("lineNumber").toNumber())+QString(" ")+VIESBase.toString());
			Engine->globalObject().setProperty("VIESBase", VIESBase);
			QJSValue VIESObject = Engine->newQObject(new VIObject(this));
			Engine->globalObject().setProperty("VIObject", VIESObject);
			Main = Engine->importModule(UserMain);
			consoleLog(Main.toString());
			for (auto i = SideModules.begin(); i != SideModules.end(); i++) {
				QJSValue m = Engine->importModule(i.value());
				Engine->globalObject().setProperty(i.key(), m);
			}
			MainClass = Main.property("main");
			//MainClass = MainClass.property("constructor");
			MainClass = MainClass.callAsConstructor();
			consoleLog("Main Class is :" + MainClass.toString());
			//Engine->installExtensions(QJSEngine::GarbageCollectionExtension);
			//consoleLog("Main Class is :"+MainClass.toString());
		}
		QJSValue MainFuncation = MainClass.property(entryPoint);
		//QJSValue MainFuncation = Main.property("main2");
		QJSValue result = MainFuncation.callWithInstance(MainClass);
		if (result.isError()) {
			qDebug() << "Uncaught exception at line" << result.property("lineNumber").toNumber() << ":" << result.toString();
		}
		//Engine->collectGarbage();
		return result;
	};
	_Public static QJSValue eval(QString code, QJSEngine* engine = VI_NULLPTR) {
		bool userEngine = true;
		if (engine == VI_NULLPTR) {
			engine = new QJSEngine();
			userEngine = false;
		}
		QJSValue rtn = engine->evaluate(code);
		if (!userEngine) {
			delete engine;
		}
		return rtn;
	};
};
