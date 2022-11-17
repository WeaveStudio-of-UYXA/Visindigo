#pragma execution_character_set("utf-8")
#include <QtCore>
#include "VIUI/VIPlayerWidget.h"
#include "VIUI/MRW/VisindigoRuntime.h"
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	qRegisterMetaType<VIMath::VI2DMatrix>("VIMath::VI2DMatrix");
	qRegisterMetaType<VIMath::VIVector2>("VIMath::VIVector2");
	qRegisterMetaType<VIMath::VIMatrix>("VIMath::VIMatrix");
	qRegisterMetaType<QList<QList<int>>>("QList<QList<int>>");
	VIRuntimeWindow* w = new VIRuntimeWindow();
	w->show();
	return app.exec();
}