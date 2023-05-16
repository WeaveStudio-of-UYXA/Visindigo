#pragma once
#include "private/VIMacro.h"

/*
* VIObject
* 此类扩展QMetaObject提供的部分功能
* 如果一个Visindigo类不是VIBasicBehavior的派生类
* 则此类必须在派生QObject之后再派生VIObject
* 并且使用宏VI_OBJECT初始化
*/

typedef QObject VISuper;
typedef QObject VIObject;

#define p_VI_OBJECT_CONTENT \
_Slot const QString getClassName() {return metaObject()->className();} \
_Slot const QString getSuperClassName() {return metaObject()->superClass()->className();} \
_Slot const QString getObjectName() {return objectName();} \
_Slot const void consoleLog(QString log) {qDebug().noquote() << "["+QDateTime::currentDateTime().toString("hh:mm:ss")+"]"<<this->getClassName()+"(\""+this->getObjectName()+"\"):"<<log;}
