#include "../VICoreFramework.h"
#include "../VIConsole.h"
#include "../VIException.h"
#include "../VIECMAScripts.h"
#include "../private/VisindigoCorePack.h"
#include "../private/VIAutoVersion.h"

#pragma execution_character_set("utf-8")
VICoreFramework* VICoreFramework::_instance = Q_NULLPTR;
VIBehaviorHost* VICoreFramework::BehaviorHost = Q_NULLPTR;
VITranslationHost* VICoreFramework::TranslationHost = Q_NULLPTR;
VIPackageManager* VICoreFramework::PackageManager = Q_NULLPTR;

def_init private_VICoreFramework::private_VICoreFramework(int& argc, char** argv) :QApplication(argc, argv) HalfVirtual;

bool private_VICoreFramework::notify(QObject* receiver, QEvent* e) {
	try {
		return QApplication::notify(receiver, e);
	}
	catch (VIException& e) {
		e.print();
		VIMultiPlatform::exit();
		return false;
	}
	return true;
}

def_init VICoreFramework::VICoreFramework(int& argc, char** argv) {
	VI_CHECK_SingletonError(this);
	PrivateCoreFramework = new private_VICoreFramework(argc, argv);
	PrivateCoreFramework->DebugModeRuntime = true;
	_instance = this;
	LanguageType = Visindigo::zh_SC;
	qRegisterMetaType<Visindigo::BehaviorState>("Visindigo::BehaviorState");
	qRegisterMetaType<Visindigo::QuantifyTickType>("Visindigo::QuantifyTickType");
	qRegisterMetaType<Visindigo::Language>("Visindigo::Language");
	PackageManager = new VIPackageManager(this);
#ifdef QT_DEBUG
	PrivateCoreFramework->DebugModeCompilation = true;
#else
	PrivateCoreFramework->DebugModeCompilation = false;
#endif
}

void printWelcome() {
	VIConsole::printLine("\033[38;2;237;28;36m===================================================================\033[0m");
	VIConsole::printLine("\033[38;2;234;54;128m╮ ╭\t─┬─\t╭──\t─┬─\t╭╮╭\t┌─╮\t─┬─\t╭─╮\t╭─╮\033[0m");
	VIConsole::printLine("\033[38;2;234;63;247m╰╮│\t │ \t╰─╮\t │ \t│││\t│ │\t │ \t│ ┐\t│ │\033[0m");
	VIConsole::printLine("\033[38;2;115;43;235m ╰╯\t─┴─\t──╯\t─┴─\t╯╰╯\t└─╯\t─┴─\t╰─╯\t╰─╯\033[0m");
	VIConsole::printLine("   \t   \t———\t  流\t   \t清  \t———\t   \t   \t");
	VIConsole::printLine("\033[38;2;50;130;246m===================================================================\033[0m");
	VIConsole::printLine("\033[38;2;234;54;128mVisindigo \033[0m" + VICoreFramework::getVisindigoVersion() + " \"" + QString(VI_VERSION_NICKNAME) + "\"" + 
#ifdef QT_DEBUG
	" \033[38;2;255;253;85m[DEBUG compilation mode]\033[0m");
#else
	" \033[38;2;255;253;85m[RELEASE compilation mode]\033[0m");
#endif
	VIConsole::printLine("\033[38;2;234;63;247mVersion Compilation Time \033[0m: \033[38;2;255;253;85m" + QString(VI_VERSION_BUILD_DATE) + " " + QString(VI_VERSION_BUILD_TIME) + " [" + VIMultiPlatform::getCPUBuildType() + "]\033[0m");
	VIConsole::printLine(VIConsole::inWarningStyle("Working Path: ") + VIConsole::inNoticeStyle(VIPathInfo::getWorkingPath()));
	VIConsole::printLine("Hello, " + VIPathInfo::getUserName() + "! Welcome to Visindigo!");
}

void VICoreFramework::init() {
	setObjectName(getVisindigoVersion());
	printWelcome();
	VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "Visindigo framework is initializing..."));
	TranslationHost = new VITranslationHost(this);
	BehaviorHost = new VIBehaviorHost(this);
	new VICommandHost(this);
	LOAD_PACKAGE(VisindigoCore::Package);
}
VIBehaviorHost* VICoreFramework::getBehaviorHostInstance() {
	if (BehaviorHost == nullptr) {
		VIConsole::printLine(VIConsole::inWarningStyle("Visindigo requires a VICoreFramework instance to initialize various program components. "));
		VIConsole::printLine(VIConsole::inErrorStyle("Before loading your package, you must first create a new VICoreFramework instance and call init()"));
		VIConsole::printLine(VIConsole::inErrorStyle("The program will exit."));
		std::exit(-1);
	}
	return BehaviorHost;
}

VITranslationHost* VICoreFramework::getTranslationHostInstance() {
	return TranslationHost;
}

void VICoreFramework::start() {
	PackageManager->startAll();
	BehaviorHost->start();
	PrivateCoreFramework->ReturnCode = qApp->exec();
}

VICoreFramework* VICoreFramework::getCoreInstance() {
	if (_instance == nullptr) {
		VIConsole::printLine(VIConsole::inWarningStyle("Visindigo requires a VICoreFramework instance to initialize various program components. "));
		VIConsole::printLine(VIConsole::inErrorStyle("Before loading your package, you must first create a new VICoreFramework instance and call init()"));
		VIConsole::printLine(VIConsole::inErrorStyle("The program will exit."));
		std::exit(-1);
	}
	return VICoreFramework::_instance;
}

int VICoreFramework::getReturnCode() {
	return PrivateCoreFramework->ReturnCode;
}

bool VICoreFramework::loadPackage(VIPackage* package) {
	return PackageManager->loadPackage(package);
}

bool VICoreFramework::isDebugModeCompilation() {
	return PrivateCoreFramework->DebugModeCompilation;
}

bool VICoreFramework::isDebugModeRuntime() {
	return PrivateCoreFramework->DebugModeRuntime;
}

bool VICoreFramework::useDebugModeRuntime() {
	if (PrivateCoreFramework->DebugModeRuntime) {
		consoleLogPure(VIConsole::inWarningStyle("The program is already running in debug mode."));
		return false;
	}
	else {
		PrivateCoreFramework->DebugModeRuntime = true;
		consoleLogPure(VIConsole::inSuccessStyle("The program is now running in debug mode."));
		return true;
	}
}

bool VICoreFramework::execCommand(QString command) {
	return VICommandHost::getInstance()->handleCommand(command);
}

QApplication* VICoreFramework::getQAppInstance() {
	return qApp;
}

void VICoreFramework::setLanguageType(Visindigo::Language type) {
	LanguageType = type;
	TranslationHost->changeLanguage(type);
}

Visindigo::Language VICoreFramework::getLanguageType() {
	return LanguageType;
}

QList<VIPackageUniqueName> VICoreFramework::getPackageNames() {
	return PackageManager->getPackageNames();
}

VIPackage* VICoreFramework::getPackage(VIPackageUniqueName name) {
	return PackageManager->getPackage(name);
}
const QString VICoreFramework::getVisindigoVersion() { 
	return QString::number(VI_VERSION_MAJOR) + "." + QString::number(VI_VERSION_MINOR) + "." + QString::number(VI_VERSION_PATCH) + "." + QString::number(VI_VERSION_BUILD); 
}

bool VICoreFramework::softCall(const QString& uniqueName, const QString& methodName, QVariantList& args, QGenericReturnArgument& result){
	//uniqueName should be package unique name, not imply yet
	const QMetaObject* TargetMetaObject = metaObject();
	int methodIndex = TargetMetaObject->indexOfMethod(QMetaObject::normalizedSignature(methodName.toStdString().c_str()));
	if (methodIndex == -1) {
		return false;
	}
	int variantCount = args.size();
	if (variantCount > 10) {
		VIConsole::printLine(VIConsole::inErrorStyle("The number of parameters exceeds the maximum limit of 10"));
		return false;
	}
	for (int i = 0; i < 10 - variantCount; i++) {
		args.append(QVariant());	
	}
	QList<QGenericArgument> argList = {};
	for (int i = 0; i < 10; i++) {
		argList.append(QGenericArgument(args[i].typeName(), args[i].data()));
	}
	bool rtn = false;
	switch (variantCount) {
	case 0:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result);
		break;
	case 1:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0]);
		break;
	case 2:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1]);
		break;
	case 3:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2]);
		break;
	case 4:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2], argList[3]);
		break;
	case 5:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2], argList[3], argList[4]);
		break;
	case 6:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2], argList[3], argList[4], argList[5]);
		break;
	case 7:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2], argList[3], argList[4], argList[5], argList[6]);
		break;
	case 8:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2], argList[3], argList[4], argList[5], argList[6], argList[7]);
		break;
	case 9:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2], argList[3], argList[4], argList[5], argList[6], argList[7], argList[8]);
		break;
	case 10:
		rtn = TargetMetaObject->method(methodIndex).invoke(this, Qt::DirectConnection, result, argList[0], argList[1], argList[2], argList[3], argList[4], argList[5], argList[6], argList[7], argList[8], argList[9]);
		break;
	}
return rtn;
};