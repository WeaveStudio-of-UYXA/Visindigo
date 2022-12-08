#pragma once
#ifdef QT_VERSION_MAJOR
#include "CE_QtMacro.h"
#endif
//This file contains the core macro definitions of the CE library
#ifndef CEL
	#define CEL

	#define CE_VERSIONINFO
		#define CE_VERSION_MAJOR 1
		#define CE_VERSION_MINOR 0
#endif

#ifndef CEL_KEYWORD
	#define CEL_KEYWORD
		#define tick unsigned int
		#define l_tick unsigned long long
		#define CE_NULLPTR nullptr
		#define operators 
		#define None
		#define DoNothing
		#define ENUM enum class
		#define Public public:
		#define Private private:
		#define Protected protected:
		#define def auto
		

	#define CEL_PYTHON_TO_CPP
		#define self this
		#define elif else if
		#define True true
		#define False false
		#define match switch
		
#endif

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


