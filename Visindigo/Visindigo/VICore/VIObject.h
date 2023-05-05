#pragma once
#include <QtCore>
#include "macro/VIMarco.h"

/*
* VIObject
* 此类扩展QMetaObject提供的部分功能
*/
VI_interface VIObject 
{
	_Public virtual const QString getClassName() PureVirtual;
	_Public virtual const QString getSuperClassName() PureVirtual;
	_Public virtual const QString getObjectName() PureVirtual;
	_Public virtual const void log(QString log) PureVirtual;
};

#define p_VI_OBJECT_CONTENT \
_Public virtual const QString getClassName() override{return metaObject()->className();} \
_Public virtual const QString getSuperClassName() override{return metaObject()->superClass()->className();} \
_Public virtual const QString getObjectName() override{return objectName();} \
_Public virtual const void log(QString log) override{qDebug() << "["<<QDateTime::currentDateTime().toString("hh:mm:ss")<<"] "<<this->getClassName()<<" ("<<this->getObjectName()<<"): "<<log;}