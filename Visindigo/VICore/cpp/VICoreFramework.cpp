#include "../VICoreFramework.h"
#include "../private/VisindigoCorePack.h"

#pragma execution_character_set("utf-8")
VICoreFramework* VICoreFramework::_instance = Q_NULLPTR;
VIBehaviorHost* VICoreFramework::BehaviorHost = Q_NULLPTR;
VILanguageHost* VICoreFramework::LanguageHost = Q_NULLPTR;

def_init VICoreFramework::VICoreFramework(int& argc, char** argv) {
	VI_CHECK_SingletonError(this);
	AppInstance = new private_VICoreFramework(argc, argv);
	AppInstance->DebugModeRuntime = true;
	_instance = this;
#ifdef QT_DEBUG
	AppInstance->DebugModeCompilation = true;
#else
	AppInstance->DebugModeCompilation = false;
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
	VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "Visindigo framework is initializing..."));
	printWelcome();
	LanguageHost = new VILanguageHost(VILanguageHost::LangType::zh_SC, VILanguageHost::LangType::zh_SC, "./Language", this);
	if (LanguageHost->loadLanguage()) {
		VIConsole::printLine(VIConsole::inSuccessStyle(getLogPrefix() + VITR("Core_LanguageHost_LoadLanguage_Success")));
	}
	else {
		VIConsole::printLine(VIConsole::inErrorStyle(getLogPrefix() + "LanguageHost cannot initiallize."));
	}
	BehaviorHost = new VIBehaviorHost(this);
	new VICommandHost(this);
	VICommand_Reg(VIECMAScripts::Command);
	LOAD_PACKAGE(VisindigoCore::Package);
	VIConsole::printLine(VIConsole::inSuccessStyle(getLogPrefix() + VITR("Core_Any_Initialized_Success").arg("Visindigo framework")));
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

VILanguageHost* VICoreFramework::getLanguageHostInstance() {
	return LanguageHost;
}
void VICoreFramework::start() {
	for(auto i = AppInstance->PackageList.begin(); i != AppInstance->PackageList.end(); i++) {
		VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "Loaded package: " + (*i)->PackageInfo->getPackageName()));
	}
	BehaviorHost->start();
	AppInstance->ReturnCode = App->exec();
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
	return AppInstance->ReturnCode;
}

bool VICoreFramework::loadPackage(VIPackage* package) {
	AppInstance->PackageList.append(package);
	package->active(VIAbstractBehavior::QuantifyTickType::T20);
	return true;
}

bool VICoreFramework::isDebugModeCompilation() {
	return AppInstance->DebugModeCompilation;
}

bool VICoreFramework::isDebugModeRuntime() {
	return AppInstance->DebugModeRuntime;
}

bool VICoreFramework::useDebugModeRuntime() {
	if (AppInstance->DebugModeRuntime) {
		consoleLogPure(VIConsole::inWarningStyle("The program is already running in debug mode."));
		return false;
	}
	else {
		AppInstance->DebugModeRuntime = true;
		consoleLogPure(VIConsole::inSuccessStyle("The program is now running in debug mode."));
		return true;
	}
}

bool VICoreFramework::execCommand(QString command) {
	return VICommandHost::getInstance()->handleCommand(command);
}

QApplication* VICoreFramework::getAppInstance() {
	return _instance->App;
}

