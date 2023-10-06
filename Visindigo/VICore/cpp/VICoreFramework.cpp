#include "../VICoreFramework.h"
#include "../VIConsole.h"
#include "../VIException.h"
#include "../VIECMAScripts.h"
#include "../private/VisindigoCorePack.h"

#pragma execution_character_set("utf-8")
VICoreFramework* VICoreFramework::_instance = Q_NULLPTR;
VIBehaviorHost* VICoreFramework::BehaviorHost = Q_NULLPTR;
VITranslationHost* VICoreFramework::TranslationHost = Q_NULLPTR;

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
#ifdef QT_DEBUG
	VIConsole::printLine("\033[38;2;234;54;128mVisindigo \033[0m" + VIVersion::getVisindigoVersion() + " \"" + VIVersion::getVisindigoNickname() + "\"" + " \033[38;2;255;253;85m[DEBUG compilation mode]\033[0m");
#else
	VIConsole::printLine("\033[38;2;234;54;128mVisindigo \033[0m" + VIVersion::getVisindigoVersion() + " \"" + VIVersion::getVisindigoNickname() + "\"" + " \033[38;2;255;253;85m[RELEASE compilation mode]\033[0m");
#endif
	VIConsole::printLine("\033[38;2;234;63;247mVersion Compilation Time \033[0m: \033[38;2;255;253;85m" + VIVersion::getVisindigoCompileTime() + " [" + VIMultiPlatform::getCPUBuildType() + "]\033[0m");
	VIConsole::printLine(VIConsole::inWarningStyle("Working Path: ") + VIConsole::inNoticeStyle(VIPathInfo::getWorkingPath()));
	VIConsole::printLine("Hello, " + VIPathInfo::getUserName() + "! Welcome to Visindigo!");
}

void VICoreFramework::init() {
	setObjectName(VIVersion::getVisindigoVersion());
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
	QStringList packageList = PrivateCoreFramework->PackageMap.keys();
	for (auto i = packageList.begin(); i != packageList.end(); i++) {
		VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "Loaded package: " + PrivateCoreFramework->PackageMap[(*i)]->getPackageMeta()->getPackageName()));
	}
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
	QString packageName = package->getPackageMeta()->getPackageName();
	if (PrivateCoreFramework->PackageMap.contains(packageName)) {
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Package name'" + packageName + "' already existed"));
		return false;
	}
	PrivateCoreFramework->PackageMap[packageName] = package;
	package->start(Visindigo::T20);
	VIConsole::printLine(VIConsole::inSuccessStyle(getLogPrefix() + "Package '" + package->getPackageMeta()->getPackageName() + "' loaded"));
	return true;
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

QList<VIPackage*> VICoreFramework::getPackageList() {
	QList<VIPackage*> rtn = {};
	for (auto i = PrivateCoreFramework->PackageMap.begin(); i != PrivateCoreFramework->PackageMap.end(); i++) {
		rtn.append(i.value());
	}
	return rtn;
}