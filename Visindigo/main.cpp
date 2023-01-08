#pragma execution_character_set("utf-8")
#include "init.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	doQRegisterMetaType();
	VIRuntimeWindow* w = new VIRuntimeWindow();
#if VI_WINDOW == VI_WINDOW_SYS
	w->showFullScreen();
#elif VI_WINDOW == VI_NO_WINDOW
	w->show();
#endif
	return app.exec();
}