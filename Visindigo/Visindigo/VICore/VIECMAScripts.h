#pragma once
#include "private/VIECMABuiltInModules.h"
#include "VICommand.h"
typedef QMap<QString, QString> ModuleMap;
class VIECMAScripts;
enum class VIECMABuiltInModule {
	System, Console
};
class private_VIECMAScripts :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	friend class VIECMAScripts;
	VI_ProtectedProperty(QJSEngine*, engine);
	VI_ProtectedProperty(QList<VIECMABuiltInModule>, BuiltInModules);
	VI_ProtectedProperty(ModuleMap, Modules);
	VI_ProtectedFlag(DelLater);
	_Signal void boot(QString fileName, QString entry = "main");
	_Protected def_init private_VIECMAScripts() {
		engine = new QJSEngine(this);
	}
	_Protected static void registerBuiltInModule(QJSEngine* engine, VIECMABuiltInModule module) {
		switch (module) {
		case VIECMABuiltInModule::System:
			engine->globalObject().setProperty("System", engine->newQObject(new VIObject()));
			break;
		case VIECMABuiltInModule::Console:
			engine->globalObject().setProperty("Console", engine->newQObject(new VIConsole()));
			break;
		default:
			break;
		}
	}
	_Slot void sideLoad(QString fileName) {
		QFileInfo fileInfo(fileName);
		QString path = fileInfo.absolutePath();
		for (auto i = Modules.begin(); i != Modules.end(); i++) {
			QJSValue ModuleObject = engine->importModule(i.value());
			engine->globalObject().setProperty(i.key(), ModuleObject);
		}
		for (auto i = BuiltInModules.begin(); i != BuiltInModules.end(); i++) {
			registerBuiltInModule(engine, *i);
		}
	}
	_Slot void onBoot(QString fileName, QString entry = "main") {
		QFileInfo fileInfo(fileName);
		QString path = fileInfo.absolutePath();
		QJSValue MainObject = engine->importModule(fileName);
		for (auto i = Modules.begin(); i != Modules.end(); i++) {
			QJSValue ModuleObject = engine->importModule(i.value());
			engine->globalObject().setProperty(i.key(), ModuleObject);
		}
		for (auto i = BuiltInModules.begin(); i != BuiltInModules.end(); i++) {
			registerBuiltInModule(engine, *i);
		}
		QJSValue MainFunction = MainObject.property(entry);
		QJSValue result = MainFunction.call();
		if (result.isError()) {
			VIConsole::printLine(getLogPrefix() + VIConsole::inErrorStyle(result.toString()));
		}
		if (DelLater) {
			deleteLater();
		}
	}
};

class VIECMAScripts :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	VI_Property(QThread*, Thread);
	VI_PrivateProperty(QWaitCondition*, ThreadWaitCondition);
	VI_PrivateProperty(QMutex*, ThreadMutex);
	VI_PrivateProperty(QList<VIECMABuiltInModule>, BuiltInModules);
	VI_PrivateProperty(ModuleMap, Modules);
	VI_PrivateProperty(private_VIECMAScripts*, VIECMAS);
	VI_Flag(OnRunning);
	VI_Flag(SideLoaded);
	_Public def_init VIECMAScripts() {
		Thread = new QThread(this);
		ThreadWaitCondition = new QWaitCondition();
		ThreadMutex = new QMutex();
		VIECMAS = VI_NULLPTR;
	}
	_Public void boot(QString fileName, QString entry = "main") {
		boot(fileName, false, entry);
	}
	_Public void threadBoot(QString fileName, QString entry = "main") {
		boot(fileName, true, entry);
	}
	_Private void boot(QString fileName, bool inThread = false, QString entry = "main") {
		private_VIECMAScripts* VIECMA = new private_VIECMAScripts();
		connect(VIECMA, &private_VIECMAScripts::boot, VIECMA, &private_VIECMAScripts::onBoot);
		VIECMA->setBuiltInModules(BuiltInModules);
		VIECMA->setModules(Modules);
		if (inThread) {
			OnRunning = true;
			VIECMA->setDelLater(true);
			VIECMA->moveToThread(Thread);
			Thread->start();
		}
		else {
			VIECMA->setDelLater(false);
		}
		emit VIECMA->boot(fileName, entry);
		if (!inThread) {
			delete VIECMA;
		}
	}
	_Public void importBuiltInModule(VIECMABuiltInModule module) {
		BuiltInModules.append(module);
	}
	_Public void importModule(QString name, QString path) {
		Modules.insert(name, path);
	}
	_Public void sideLoad(QString fileName) {
		if (SideLoaded) {
			return;
		}
		SideLoaded = true;
		VIECMAS = new private_VIECMAScripts();
		VIECMAS->setBuiltInModules(BuiltInModules);
		VIECMAS->setModules(Modules);
		VIECMAS->sideLoad(fileName);
	}
	_Public void unload() {
		if (!SideLoaded) {
			return;
		}
		SideLoaded = false;
		delete VIECMAS;
		VIECMAS = VI_NULLPTR;
	}
	_Public QJSValue getGlobalObject(QString name) {
		if (SideLoaded) {
			return VIECMAS->engine->globalObject();
		}
		return QJSValue();
	}
	private slots: void onExit() {
		OnRunning = false;
		ThreadWaitCondition->wakeAll();
		Thread->wait();
		Thread->quit();
	}
	_Public def_del ~VIECMAScripts() {
		if (OnRunning) {
			onExit();
		}
		delete Thread;
		delete ThreadWaitCondition;
		delete ThreadMutex;
		if (VIECMAS != VI_NULLPTR) {
			delete VIECMAS;
		}
	}
	_Public VICommand_Handler(Command) {
		VICommand_Name("ecma") {
			VIConsole::printLine("VIECMA Scripts Engine");
			return true;
		}
	};
};
