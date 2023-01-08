#pragma once
#include <QtCore>
#include "macro/VIJSGlobal_m.h"
#include "../Visindigo/VIObjects/macro/VIGlassConvention.h"
#include "../CommonEdit/CECore/CEMacro.h"
class VIJSGlobal {
public:
	static QMutex VIJSMutex;
	static QWaitCondition VIJSWait;
	static QString Path;
	static QString getAbsolutePathOf(QString path) {
		if (path.startsWith("./")) {
			QString p = path.replace("./", Path + "/");
			qDebug() << p;
			return p;
		}
		else {
			return path;
		}
	}
};