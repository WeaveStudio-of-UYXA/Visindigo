#include "../VIFramework.h"
#pragma execution_character_set("utf-8")
VIFramework* VIFramework::Instance = Q_NULLPTR;
VIBehaviorHost* VIFramework::BehaviorHost = Q_NULLPTR;
VILanguageHost* VIFramework::LanguageHost = Q_NULLPTR;

def_init VIFramework::VIFramework(int& argc, char** argv) {
	App = new VIApplication(argc, argv);
	Data = new private_VIFramework();
	Data->DebugModeRuntime = true;
#ifdef QT_DEBUG
	Data->DebugModeCompilation = true;
#else
	Data->DebugModeCompilation = false;
#endif
}

void VIFramework::init() {
	setObjectName(VIVersion::getVisindigoVersion());
	VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "Visindigo framework is initializing..."));
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
	VIConsole::printLine(VIConsole::inWarningStyle("Working Path: ") + VIConsole::inNoticeStyle(VIDocument::getWorkingPath()));
	VIConsole::printLine("Hello, " + VIDocument::getUserName() + "! Welcome to Visindigo!");
	VIFramework::Instance = this;
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
	VIConsole::printLine(VIConsole::inSuccessStyle(getLogPrefix() + VITR("Core_Any_Initialized_Success").arg("Visindigo framework")));
}
VIBehaviorHost* VIFramework::getBehaviorHostInstance() {
	if (BehaviorHost == nullptr) {
		VIConsole::printLine(VIConsole::inWarningStyle("Visindigo requires a VIFramework instance to initialize various program components. "));
		VIConsole::printLine(VIConsole::inErrorStyle("Before loading your package, you must first create a new VIFramework instance and call init()"));
		VIConsole::printLine(VIConsole::inErrorStyle("The program will exit."));
		std::exit(-1);
	}
	return BehaviorHost;
}

VILanguageHost* VIFramework::getLanguageHostInstance() {
	return LanguageHost;
}
void VIFramework::start() {
	BehaviorHost->start();
	Data->ReturnCode = App->exec();
}

VIFramework* VIFramework::getInstance() {
	if (VIFramework::Instance == nullptr) {
		VIConsole::printLine("Visindigo requires a VIFramework instance to initialize various program components. \
Before loading your package, you must first create a new VIFramework instance.\nThe program will exit.\n");
		std::exit(-1);
	}
	return VIFramework::Instance;
}

int VIFramework::getReturnCode() {
	return Data->ReturnCode;
}

bool VIFramework::loadPackage(VIPackage* package) {
	Data->PackageList.append(package);
	package->active(VIAbstractBehavior::QuantifyTickType::T20);
	return true;
}

bool VIFramework::isDebugModeCompilation() {
	return Data->DebugModeCompilation;
}

bool VIFramework::isDebugModeRuntime() {
	return Data->DebugModeRuntime;
}

bool VIFramework::useDebugModeRuntime() {
	if (Data->DebugModeRuntime) {
		consoleLogPure(VIConsole::inWarningStyle("The program is already running in debug mode."));
		return false;
	}
	else {
		Data->DebugModeRuntime = true;
		consoleLogPure(VIConsole::inSuccessStyle("The program is now running in debug mode."));
		return true;
	}
}

bool VIFramework::execCommand(QString command) {
	return VICommandHost::getInstance()->handleCommand(command);
}