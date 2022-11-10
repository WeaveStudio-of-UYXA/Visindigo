#pragma execution_character_set("utf-8")
#include <QtCore>
#include "VIUI/VIPlayerWidget.h"
#include "VIUI/MRW/VisindigoRuntime.h"
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	//AWidget* w = new AWidget();
	VIRuntimeWindow* w = new VIRuntimeWindow();
	w->show();
	return app.exec();
}