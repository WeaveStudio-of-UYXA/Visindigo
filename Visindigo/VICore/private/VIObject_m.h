#pragma once
#include "VIMacro.h"

#define VI_OBJECT p_VI_OBJECT_CONTENT

#define p_VI_OBJECT_CONTENT \
_Slot const QString getClassName() {return metaObject()->className();} \
_Slot const QString getSuperClassName() {return metaObject()->superClass()->className();} \
_Slot const QString getObjectName() {return objectName();} \
_Slot const void consoleLog(QString log) {qDebug().noquote() << getLogPrefix()<<log;}\
_Slot QString getLogPrefix() {\
	return "[" + QDateTime::currentDateTime().toString("hh:mm:ss") + "]" + this->getClassName() + "(\"" + this->getObjectName() + "\"):";\
}\
_Slot const void consoleLogPure (QString log) {qDebug().noquote() << log;}
