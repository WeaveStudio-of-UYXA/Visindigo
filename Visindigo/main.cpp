#include"ah.h"
#pragma execution_character_set("utf-8")
#include "VITrans/VIServer.h"
#include "PythonAPI/PythonAPI.h"
#include "global_value.h"
#include "GUI/VIGUI.h"
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	VIServer* VServer = new VIServer();
	PythonAPI* PyAPI = new PythonAPI(L"./Python39");
	Global::PyAPI = PyAPI;
	Global::VServer = VServer;
	VIGUI *GUI = new VIGUI();
	GUI->show();
	return app.exec();
}