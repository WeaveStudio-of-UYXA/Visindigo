#pragma once
#include <QtCore>

//This file contains the core macro definitions of the CE library
#define defAs :public

#define VI_NULLPTR Q_NULLPTR


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
#define ENUM enum class

#define VI_Property(Type, name) public:Type name;void set##name(Type value){this->name = value;}Type get##name(){return name;}
#define VI_PrivateProperty(Type, name) private:Type name;private: void set##name(Type value){this->name = value;}public:Type get##name(){return name;}
#define VI_Flag(name) public:bool name;void set##name(bool value){this->name = value;}bool is##name(){return name;}
#define VI_PrivateFlag(name) private:bool name;private: void set##name(bool value){this->name = value;}public:bool is##name(){return name;}

#define def_init
#define def_del
#define def_copy
#define def_move
#define PASS
#define VI_NO_PARENT

#define def auto
#define elif else if
#define True true
#define False false



//We provide macros that are supported by Visual Studio(strictly speaking,by WindowsAPI) by default, 
// but are not actually part of standard C++.
//When the code leaves the environment, we don't want these macros to report errors.

#ifndef FALSE
#define FALSE false
#define TRUE true
#endif

#ifndef NULL
#define NULL 0
#endif