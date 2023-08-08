#include "../VIECMAScripts.h"
/*
private_VIECMAScripts
*/

def_init private_VIECMAScripts::private_VIECMAScripts() {
	engine = new QJSEngine(this);
}

void private_VIECMAScripts::registerBuiltInModule(QJSEngine* engine, VIECMABuiltInModule module) {
	switch (module) {
	case VIECMABuiltInModule::System:
		engine->globalObject().setProperty("System", engine->newQObject(new VIObject()));
		break;
	case VIECMABuiltInModule::Console:
		engine->globalObject().setProperty("Console", engine->newQObject(new private_VIECMA_Console()));
		break;
	default:
		break;
	}
}

void private_VIECMAScripts::importVIObject(VIObject* obj) {
	VIObjectModules.append(obj);
}

void private_VIECMAScripts::sideLoad(const QString& fileName) {
	QFileInfo fileInfo(fileName);
	QString path = fileInfo.absolutePath();
	QJSValue MainObject = engine->importModule(path);
	for (auto i = Modules.begin(); i != Modules.end(); i++) {
		QJSValue ModuleObject = engine->importModule(i.value());
		engine->globalObject().setProperty(i.key(), ModuleObject);
	}
	for (auto i = BuiltInModules.begin(); i != BuiltInModules.end(); i++) {
		registerBuiltInModule(engine, *i);
	}
}

void private_VIECMAScripts::onBoot(const QString& fileName, const QString& entry ) {
	if (InThread) {
		ThreadMutex->lock();
	}
	for (auto i = BuiltInModules.begin(); i != BuiltInModules.end(); i++) {
		registerBuiltInModule(engine, *i);
	}
	for (auto i = VIObjectModules.begin(); i != VIObjectModules.end(); i++) {
		engine->globalObject().setProperty((*i)->getObjectName(), engine->newQObject(*i));
	}
	QFileInfo fileInfo(fileName);
	QString path = fileInfo.absolutePath();
	qDebug() << path;
	QJSValue MainObject = engine->importModule(fileName);
	qDebug() << MainObject.toString();
	for (auto i = Modules.begin(); i != Modules.end(); i++) {
		QJSValue ModuleObject = engine->importModule(i.value());
		engine->globalObject().setProperty(i.key(), ModuleObject);
	}
	
	QJSValue MainFunction = MainObject.property(entry);
	QJSValue result = MainFunction.call();
	if (result.isError()) {
		VIConsole::printLine(getLogPrefix() + VIConsole::inErrorStyle(result.toString()));
	}
	qDebug() << result.toString();
	consoleLog("VIECMA processing " + fileName + " finished.");
	if (InThread) {
		ThreadMutex->unlock();
	}
	emit finished();
	for (auto i = VIObjectModules.begin(); i != VIObjectModules.end(); i++) {
		(*i)->deleteLater();
		(*i) = VI_NULLPTR;
	}
	if (DelLater) {
		
		deleteLater();
	}
}
/*
VIECMAScripts
*/
def_init VIECMAScripts::VIECMAScripts() {
	Thread = new QThread(this);
	ThreadWaitCondition = new QWaitCondition();
	ThreadMutex = new QMutex();
	VIECMAS = VI_NULLPTR;
	OnRunning = false;
	SideLoaded = false;
}

void VIECMAScripts::boot(const QString& fileName, const QString& entry) {
	boot(fileName, false, entry);
}

void VIECMAScripts::threadBoot(const QString& fileName, const QString& entry ) {
	boot(fileName, true, entry);
}

void VIECMAScripts::boot(QString fileName, bool inThread , QString entry ) {
	if (OnRunning) {
		return;
	}
	private_VIECMAScripts* VIECMA = new private_VIECMAScripts();
	connect(VIECMA, &private_VIECMAScripts::boot, VIECMA, &private_VIECMAScripts::onBoot);
	connect(VIECMA, &private_VIECMAScripts::finished, this, &VIECMAScripts::finished);
	connect(VIECMA, &private_VIECMAScripts::finished, this, &VIECMAScripts::onExit);
	VIECMA->setBuiltInModules(BuiltInModules);
	VIECMA->setModules(Modules);
	VIECMA->setVIObjectModules(VIObjectModules);
	VIECMA->setThreadMutex(ThreadMutex);
	VIECMA->setThreadWaitCondition(ThreadWaitCondition);
	VIECMA->setInThread(inThread);
	if (inThread) {
		OnRunning = true;
		VIECMA->setDelLater(true);
		VIECMA->moveToThread(Thread);
		Thread->start();
	}
	else {
		VIECMA->setDelLater(false);
	}
	consoleLog("VIECMA processing " + fileName + " ...");
	emit VIECMA->boot(fileName, entry);
	if (!inThread) {
		delete VIECMA;
	}
}

void VIECMAScripts::importBuiltInModule(VIECMABuiltInModule module) {
	BuiltInModules.append(module);
}

void VIECMAScripts::importModule(const QString& name, const QString& path) {
	Modules.insert(name, path);
}

void VIECMAScripts::importVIObject(VIObject* obj) {
	VIObjectModules.append(obj);
}

void VIECMAScripts::sideLoad(QString fileName) {
	if (SideLoaded) {
		return;
	}
	if (OnRunning) {
		return;
	}
	SideLoaded = true;
	VIECMAS = new private_VIECMAScripts();
	VIECMAS->setBuiltInModules(BuiltInModules);
	VIECMAS->setModules(Modules);
	VIECMAS->sideLoad(fileName);
}

void VIECMAScripts::unload() {
	if (!SideLoaded) {
		return;
	}
	SideLoaded = false;
	delete VIECMAS;
	VIECMAS = VI_NULLPTR;
}

QJSValue VIECMAScripts::getGlobalObject(QString name) {
	if (SideLoaded) {
		return VIECMAS->engine->globalObject();
	}
	return QJSValue();
}

void VIECMAScripts::onExit() {
	OnRunning = false;
	ThreadWaitCondition->wakeAll();
	Thread->exit();
}

def_del VIECMAScripts::~VIECMAScripts() {
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