#pragma once
#include "VIVersion.h"
//此文件定义VI工程

class VIProject :public QObject
{
	Q_OBJECT;
	_Public struct ProjectInfo {
		QString Name;
		QString Path;
		QString Author;
		VIVersion Version;
	};
	_Public def_init VIProject();
};