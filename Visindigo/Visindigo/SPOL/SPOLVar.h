#pragma once
#include "SPOLBaseObject.h"
#include "SPOLBaseVar.h"

class SPOLCallable :public SPOLBaseObject {
	_Private bool isQuoteObject();
	_Public def_init SPOLCallable(QString objectName = "UNKNOWN") { ObjectName = objectName; }
	_Public void __call__(SPOLCallable* self) {}//括号调用
	_Public void __add__(SPOLCallable* self) {}//操作符+
	_Public void __sub__(SPOLCallable* self) {}//操作符-
	_Public void __mul__(SPOLCallable* self) {}//操作符*
	_Public void __div__(SPOLCallable* self) {}//操作符/
	_Public void __mod__(SPOLCallable* self) {}//操作符%
	_Public void __init__(SPOLCallable* self) {}//操作符=
	_Public void __at__(SPOLCallable* self) {}//操作符[]
	_Public void __equal__(SPOLCallable* self) {}//操作符==
	_Public void __more__(SPOLCallable* self) {}//操作符>
	_Public void __less__(SPOLCallable* self) {}//操作符<
	_Public void __and__(SPOLCallable* self) {}//操作符 and
	_Public void __or__(SPOLCallable* self) {}//操作符 or
	_Public void __not__(SPOLCallable* self) {}//操作符 not
	_Public void __var__(SPOLCallable* self) {}//直接调用
};

class SPOLVar :public SPOLCallable {
	_Private SPOLBaseVar value;
	_Public def_init SPOLVar();
	_Public SPOLBaseVar* getValuePointer();
	_Public void __var__(SPOLCallable* self);
	
};

class SPOLList :public SPOLCallable {
	_Private QVector<SPOLCallable*> value;
	_Public def_init SPOLList();
	_Public void __var__(SPOLCallable* self);
};