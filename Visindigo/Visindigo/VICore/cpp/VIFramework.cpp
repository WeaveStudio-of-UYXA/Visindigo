#include "../VIFramework.h"
#pragma execution_character_set("utf-8")
VIFramework* VIFramework::Instance = Q_NULLPTR;
VIBehaviorHost* VIFramework::BehaviorHost = Q_NULLPTR;

def_init VIFramework::VIFramework(int& argc, char** argv) {
	App = new QApplication(argc, argv);
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
	qDebug().noquote() << "\033[38;2;237;28;36m===================================================================\033[0m";
	qDebug().noquote() << "\033[38;2;234;54;128m╮ ╭\t─┬─\t╭──\t─┬─\t╭╮╭\t┌─╮\t─┬─\t╭─╮\t╭─╮\033[0m";
	qDebug().noquote() << "\033[38;2;234;63;247m╰╮│\t │ \t╰─╮\t │ \t│││\t│ │\t │ \t│ ┐\t│ │\033[0m";
	qDebug().noquote() << "\033[38;2;115;43;235m ╰╯\t─┴─\t──╯\t─┴─\t╯╰╯\t└─╯\t─┴─\t╰─╯\t╰─╯\033[0m";
	qDebug().noquote() << "\033[38;2;50;130;246m===================================================================\033[0m";
#ifdef QT_DEBUG
	qDebug().noquote() << "\033[38;2;234;54;128mVisindigo \033[0m" + VIVersion::getVisindigoVersion() + " \"" + VIVersion::getVisindigoNickname() + "\"" + " \033[38;2;255;253;85m[DEBUG compilation mode]\033[0m";
#else
	qDebug().noquote() << "\033[38;2;234;54;128mVisindigo \033[0m" + VIVersion::getVisindigoVersion() + " \"" + VIVersion::getVisindigoNickname() + "\"" + " \033[38;2;255;253;85m[RELEASE compilation mode]\033[0m";
#endif
	qDebug().noquote() << "\033[38;2;234;63;247mVersion Compilation Time \033[0m: \033[38;2;255;253;85m" + VIVersion::getVisindigoCompileTime() + " [" + VIMultiPlatform::getCPUBuildType() + "]\033[0m\n";
	consoleLogPure(VIConsole::inNoticeStyle(getLogPrefix() + "Visindigo framework is starting..."));
	VIFramework::Instance = this;
	BehaviorHost = new VIBehaviorHost(this);
	consoleLogPure(VIConsole::inSuccessStyle(getLogPrefix() + "Visindigo framework initialized."));
}
VIBehaviorHost* VIFramework::getBehaviorHostInstance() {
	if (BehaviorHost == nullptr) {
		qDebug().noquote() << VIConsole::inWarningStyle("Visindigo requires a VIFramework instance to initialize various program components. ");
		qDebug().noquote() << VIConsole::inErrorStyle("Before loading your package, you must first create a new VIFramework instance and call init()");
		qDebug().noquote() << VIConsole::inErrorStyle("The program will exit.");
		std::exit(-1);
	}
	return BehaviorHost;
}

void VIFramework::start() {
	BehaviorHost->start();
	Data->ReturnCode = App->exec();
}

VIFramework* VIFramework::getInstance() {
	if (VIFramework::Instance == nullptr) {
		qDebug().noquote() << "Visindigo requires a VIFramework instance to initialize various program components. \
Before loading your package, you must first create a new VIFramework instance.\nThe program will exit.\n";
		std::exit(-1);
	}
	return VIFramework::Instance;
}

int VIFramework::getReturnCode() {
	return Data->ReturnCode;
}

bool VIFramework::loadPackage(VIPackage* package) {
	package->Framework = this;
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