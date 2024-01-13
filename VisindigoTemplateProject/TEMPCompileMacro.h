/*
* 本文件用于定义编译宏，以便在不同的编译选项下，正确地导出或导入类、函数、变量等
* 如果你不知道如何使用此文件，请不要修改此文件
*/
#pragma once
#include <VICore>
#if VI_VERSION_MAJOR != 1 || VI_VERSION_MINOR != 2 || VI_VERSION_PATCH != 0
 #error "This template is only for Visindigo 1.2.0, please use the correct version of Visindigo!"
#endif

#define $safeprojectname$_USER
#ifdef $safeprojectname$_EVERYWHERE // 此宏在非Dll编译选项中项目内部定义，参见项目调试属性->C/C++ ->预定义宏
	#undef $safeprojectname$_USER
#endif
#ifdef $safeprojectname$_DEVELOPER // 此宏在Dll编译选项中内部定义，参见项目调试属性->C/C++ ->预定义宏
	#undef $safeprojectname$_USER
#endif

//Visindigo提供的权限标识宏_Public、_Private、_Protected、_Slot、_Signal也在内部定义，防止QT在MOC时出现错误

#ifdef _MSC_VER
	#if defined $safeprojectname$_EVERYWHERE
		#define $safeprojectname$PublicAPI 
	#elif defined $safeprojectname$_DEVELOPER
		#define $safeprojectname$PublicAPI __declspec(dllexport)
	#elif defined $safeprojectname$_USER
		#define $safeprojectname$PublicAPI __declspec(dllimport)
	#else
		#define $safeprojectname$PublicAPI
	#endif
#endif

#define $safeprojectname$PrivateAPI