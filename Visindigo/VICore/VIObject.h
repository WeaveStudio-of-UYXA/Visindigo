#pragma once
#include "VIException.h"
#include "private/VIMacro.h"
/*
* QObject
* 此类扩展QMetaObject提供的部分功能
* 如果一个Visindigo类不是VIBasicBehavior的派生类
* 则此类必须在派生QObject之后再派生QObject
* 并且使用宏VI_OBJECT初始化
*/

class VIPublicAPI VIAbstractObject
{
	_Public virtual const QString getClassName() PureVirtual;
	_Public virtual const QString getSuperClassName() PureVirtual;
	_Public virtual const QString getObjectName() PureVirtual;
	_Public virtual const void consoleLog(QString log) PureVirtual;
	_Public virtual const void consoleLogPure(QString log) PureVirtual;
	_Public virtual void throwThis() PureVirtual;
};
using VIBaseObject = VIAbstractObject;
using VISuper = QObject;

#define VI_OBJECT p_VI_OBJECT_CONTENT

#define p_VI_OBJECT_CONTENT \
_Slot const QString getClassName() {return metaObject()->className();} \
_Slot const QString getSuperClassName() {return metaObject()->superClass()->className();} \
_Slot const QString getObjectName() {return objectName();} \
_Slot const void consoleLog(QString log) {qDebug().noquote() << getLogPrefix()<<log;}\
_Slot QString getLogPrefix() {\
	return "[" % QDateTime::currentDateTime().toString("hh:mm:ss") % "]" % this->getClassName() % "(" % this->getObjectName() % "):";\
}\
_Slot const void consoleLogPure (QString log) {qDebug().noquote() << log;}\
_Slot void throwThis(){throw VIException("Unknown Exception throwed by class "+this->getClassName()+",instance name "+this->getObjectName()),"please check your code";}


class VIPublicAPI VIObject :public VISuper, VIBaseObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIObject(VISuper* parent = VI_NULLPTR) :VISuper(parent) {};
};

