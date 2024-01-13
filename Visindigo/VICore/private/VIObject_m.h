﻿#pragma once
#include "VIMacro.h"

#define Visindigo_ROOT "cn.yxgeneral.weavestudio.visindigo"
#define Unique_Visindigo_Core Visindigo_ROOT ".core"
#define Unique_Visindigo_Widget Visindigo_ROOT ".widget"
#define Unique_Visindigo_ARCP Visindigo_ROOT ".arcp"
#define Unique_Visindigo_UIJson Visindigo_ROOT ".uijson"
#define Unique_Visindigo_GitTools Visindigo_ROOT ".gittools"
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
