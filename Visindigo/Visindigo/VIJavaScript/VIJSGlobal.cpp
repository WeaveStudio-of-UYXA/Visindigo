#include "VIJSGlobal.h"

QMutex VIJSGlobal::VIJSMutex;
QWaitCondition VIJSGlobal::VIJSWait;
QString VIJSGlobal::Path = "";