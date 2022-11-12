#pragma once
#include <QtCore>
class VIJSGlobal {
public:
	static QMutex VIJSMutex;
	static QWaitCondition VIJSWait;
};


#define VIJSHostWait VIJSGlobal::VIJSWait.wait(&VIJSGlobal::VIJSMutex)
#define VIJSHostWake VIJSGlobal::VIJSWait.wakeAll()