#pragma once
#include <QtCore>
#include "VICompileMacro.h"
#include "VisindigoNamespace.h"
//This file contains the core macro definitions of the CE library
#ifndef VI_MACRO
#define VI_MACRO
#define VI_NULLPTR Q_NULLPTR
#define VI_NULL Q_NULLPTR
#define _Public public:
#define _Private private:
#define _Protected protected:
#define _Slot public Q_SLOTS:
#define _Signal Q_SIGNALS:
#define PureVirtual = 0
#define HalfVirtual {}
#define InitAsNull = Q_NULLPTR
#define InitAsZero = 0
#define InitAsNone = {}

#define VI_interface class

#define VI_STATIC_CLASS(name) private: name(){} 
#define VI_Property(Type, name) public:Type name;void set##name(Type value){this->name = value;}Type get##name(){return name;}
#define VI_PrivateProperty(Type, name) private:Type name;private: void set##name(Type value){this->name = value;}public:Type get##name(){return name;}
#define VI_ProtectedProperty(Type, name) protected:Type name;protected: void set##name(Type value){this->name = value;}public:Type get##name(){return name;}

#define VI_Flag(name) public:bool name;void set##name(bool value){this->name = value;}bool is##name(){return name;}
#define VI_PrivateFlag(name) private:bool name;private: void set##name(bool value){this->name = value;}public:bool is##name(){return name;}
#define VI_ProtectedFlag(name) protected:bool name;protected: void set##name(bool value){this->name = value;}public:bool is##name(){return name;}

#define def_init
#define def_del
#define def_copy
#define def_move
#define PASS
#define VI_NO_PARENT

#define VI_MUST_INHERIT(name) public: virtual void __INHERIT_FLAG_##name__() PureVirtual;
#define VI_HAS_INHERIT(name) public: virtual void __INHERIT_FLAG_##name__() HalfVirtual;

#define VI_Singleton(name) protected: static name* _instance; public: static name* getInstance(){return _instance;} protected: void setInstance(name* value){_instance = value;}
#define VI_CHECK_SingletonError \
if (this->_instance != VI_NULLPTR)\
	{throw VISingletonError("Singleton Error: "+QString(this->metaObject()->className())+\
	" has already been created!", "Check your code to ensure that this class is only created once.\nThis exception is thrown on line [ "+\
	QString::number(__LINE__)+" ] of file: \n"+__FILE__);}
#define VI_Singleton_StaticInit(name) name* name::_instance = VI_NULLPTR;
#define VI_Singleton_Init VI_CHECK_SingletonError else{_instance = this;}
#define VI_CHECK_NullPointerError(name) \
if (name == VI_NULLPTR)\
	{throw VINullPointerError("NullPointer Error: Pointer '"+##name+\
	"' should not be null", "Check your code to ensure that the memory pointed to by this pointer has been initialized before access, or avoid access after null.\nThis exception is thrown on line [ "+\
	QString::number(__LINE__)+" ] of file: \n"+__FILE__);}



#endif