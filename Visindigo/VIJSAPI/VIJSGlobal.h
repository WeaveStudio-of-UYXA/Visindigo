#pragma once
#include <QtCore>
class VIJSGlobal {
public:
	static QMutex VIJSMutex;
	static QWaitCondition VIJSWait;
	static QString Path;
	static QString getAbsolutePathOf(QString path) {
		if (path.startsWith("./")) {
			return path.replace("./", Path + "/");
		}else{
			return path;
		}
	}
};

#define VIJSHostWait VIJSGlobal::VIJSWait.wait(&VIJSGlobal::VIJSMutex)
#define VIJSHostWake VIJSGlobal::VIJSWait.wakeAll()