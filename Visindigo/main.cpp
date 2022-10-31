#pragma execution_character_set("utf-8")
#include <QtCore>
#include <Python.h>

int main(int* argc, char* argv[]) {
	qDebug() << "Hello World";
	Py_SetPythonHome(L"./Python");
	qDebug() << "Visindigo正在初始化内置Python核心";
	Py_Initialize();
	qDebug() << "Visindigo的Python核心下具有以下目录:";
	PyRun_SimpleString("import os");
	PyRun_SimpleString("print(os.listdir())");
	return 0;
}