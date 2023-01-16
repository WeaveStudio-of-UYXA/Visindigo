#pragma once
#include "SPOLObject.h"

class SPOLSyntax :public QObject {
	Q_OBJECT;
	_Public SPOLExecObject exec(QString code);
	_Public SPOLExecObject execFile(QString path);
	_Private SPOLExecObject execALine(QStringList::iterator i);
};