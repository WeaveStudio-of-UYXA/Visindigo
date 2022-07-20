#pragma once
#include "../ah.h"
class PythonAPI :public QThread
{
	Q_OBJECT
public:
	PythonAPI(const wchar_t PythonHome[], QObject* parent = Q_NULLPTR) {
		Py_SetPythonHome((wchar_t*)(PythonHome));
	}
	void run() {
		qDebug() << "Visindigo正在初始化内置Python核心";
		Py_Initialize();
		//qDebug() << "Visindigo的Python核心下具有以下目录:";
		//PyRun_SimpleString("import os");
		//PyRun_SimpleString("print(os.listdir())");
		//qDebug() << "执行Users_Data/repos/PyVIApplication1/main.py";
		//PyObject* pModule = PyImport_ImportModule("Users_Data.repos.PyVIApplication1.main");
		PyRun_SimpleString("import Users_Data.repos.PyVIApplication1.main as UserMain");
		qDebug() << "定位VImain主函数";
		PyRun_SimpleString("main = UserMain.Main()");
		//PyObject* pFunc = PyObject_GetAttrString(pModule, "VImain");
		//PyObject_CallFunction(pFunc, NULL);
		qDebug() << "Visindigo正在关闭内置Python核心";
		Py_Finalize();
	}
};