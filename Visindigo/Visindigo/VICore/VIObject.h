#pragma once
#include <QtCore>
#include "macro/VIMarco.h"

/*
* VIObject
* 此类扩展QMetaObject提供的部分功能
* 如果一个Visindigo类不是VIBasicBehavior的派生类
* 则此类必须在派生QObject之后再派生VIObject
* 并且使用宏VI_OBJECT初始化
*/

class VIAbstractObject
{
	_Public virtual const QString getClassName() PureVirtual;
	_Public virtual const QString getSuperClassName() PureVirtual;
	_Public virtual const QString getObjectName() PureVirtual;
	_Public virtual const void consoleLog(QString log) PureVirtual;
};

typedef QObject VISuper;
typedef VIAbstractObject VIBaseObject;

#define p_VI_OBJECT_CONTENT \
_Slot const QString getClassName() {return metaObject()->className();} \
_Slot const QString getSuperClassName() {return metaObject()->superClass()->className();} \
_Slot const QString getObjectName() {return objectName();} \
_Slot const void consoleLog(QString log) {qDebug().noquote() << "["+QDateTime::currentDateTime().toString("hh:mm:ss")+"]"<<this->getClassName()+"(\""+this->getObjectName()+"\"):"<<log;}

class VIObject :public VISuper, VIBaseObject
{
	Q_OBJECT;
	p_VI_OBJECT_CONTENT;
	_Public Q_INVOKABLE def_init VIObject(VISuper* parent = VI_NULLPTR) :VISuper(parent) {};
};