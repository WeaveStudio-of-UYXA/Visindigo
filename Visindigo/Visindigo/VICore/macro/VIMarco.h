#pragma once

#include <QtCore>

//This file contains the core macro definitions of the CE library
#define tick unsigned int
#define l_tick unsigned long long
#define CE_NULLPTR nullptr
#define operators 
#define PASS
#define ENUM enum class
#define _Public public:
#define _Private private:
#define _Protected protected:
#define def auto
#define def_init
#define def_del
#define def_copy
#define def_move
#define __Deprecated__(reason) [[deprecated(reason)]]

#define elif else if
#define True true
#define False false
#define _Slot public Q_SLOTS:
#define _Signal Q_SIGNALS:

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