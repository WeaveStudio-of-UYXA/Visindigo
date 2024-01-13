#pragma once
#include "private/VIObject_m.h"
#include "VIException.h"
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

class VIPublicAPI VIObject :public VISuper, VIBaseObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIObject(VISuper* parent = VI_NULLPTR) :VISuper(parent) {};
};
