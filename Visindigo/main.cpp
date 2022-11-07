#pragma execution_character_set("utf-8")
#include <QtCore>
#include <Python.h>
#include "VisindigoUI/VIPlayerWidget.h"
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Py_SetPythonHome(L"./Python");
	qDebug() << "Visindigo正在初始化内置Python核心";
	Py_Initialize();
	qDebug() << "Visindigo的Python核心下具有以下目录:";
	PyRun_SimpleString("import os");
	PyRun_SimpleString("print(os.listdir())");
	PyRun_SimpleString("print(os.getcwd())");
	PyRun_SimpleString("import Users_Data.repos.PyVIApplication1.main as UserMain");
	qDebug() << "定位VImain主函数";
	PyRun_SimpleString("main = UserMain.Main()");
	AWidget* w = new AWidget();
	w->show();
	return app.exec();
}