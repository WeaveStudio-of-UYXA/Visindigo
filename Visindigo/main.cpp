#pragma execution_character_set("utf-8")
#include "init.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	doQRegisterMetaType();
	VIRuntimeWindow* w = new VIRuntimeWindow();
	w->show();
	return app.exec();
}