#pragma once
#include <QtCore>
#include "macro/VIJSGlobal_m.h"

class VIJSGlobal {
public:
	static QMutex VIJSMutex;
	static QWaitCondition VIJSWait;
	static QString Path;
	static QString getAbsolutePathOf(QString path) {
		if (path.startsWith("./")) {
			return path.replace("./", Path + "/");
		}
		else {
			return path;
		}
	}
};