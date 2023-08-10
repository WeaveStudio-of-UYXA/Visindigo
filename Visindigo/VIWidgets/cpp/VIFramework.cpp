#include "../VIFramework.h"
#include "../private/VisindigoWidgetsPack.h"

VIFramework* VIFramework::Instance = VI_NULLPTR;

def_init VIFramework::VIFramework(int& argc, char** argv) :VICoreFramework(argc, argv) {
	PaletteGroup = VI_NULLPTR;
	StyleSheetManeger = VI_NULLPTR;
	Instance = this;
}

void VIFramework::init() {
	VICoreFramework::init();
	PaletteGroup = new VIPaletteGroup();
	StyleSheetManeger = new VIDynamicStyleSheetManager(this);
	LOAD_PACKAGE(VisindigoWidgets::Package);
}

void VIFramework::start() {
	VICoreFramework::start();
}

VIFramework* VIFramework::getInstance() {
	if (Instance == nullptr) {
		VIConsole::printLine(VIConsole::inWarningStyle("Visindigo requires a VIFramework instance to initialize various program components. "));
		VIConsole::printLine(VIConsole::inErrorStyle("Before loading your package, you must first create a new VIFramework instance and call init()"));
		VIConsole::printLine(VIConsole::inErrorStyle("The program will exit."));
		std::exit(-1);
	}
	return VIFramework::Instance;
}