#pragma once
//此项目控制部署目标平台
//#define LINUX_DEPLOY //暂时不支持
//#define ANDROID_DEPLOY //arm64-v8a
//#define ANDROID_DEPLOY_OLD //armeabi-v7a
//#define WINDOWS_DEPLOY_32 //x86_32
#define WINDOWS_DEPLOY //x86_64

//此项目控制是否使用3D
//#define VI_USE_3D

//此项目控制是否使用2D
#define VI_USE_2D

//此项目控制是否引入Visindigo.JS
#define VI_USE_JSENGINE

//此项目控制顶层QWidget是否应该被QOpenGLWidget取代
#define VI_USE_OPENGLWIDGET

//此项目控制VICoordinate的浮点置信度
#define VI_COORDINATE_CONFIDENCE 0.0000000001
//我劝你最好别改这个
//1e9也不代表甚么纳米，只是代表内部精度。

//编译导出选项
//使用Debug、Release编译时，预置VI_EVERYWHERE
//使用DllDebug、DllRelease编译时，预置VI_DEVELOPER
//上述两种情况都不是时，预置VI_USER

#define VI_USER
#ifdef VI_EVERYWHERE
	#undef VI_USER
#endif
#ifdef VI_DEVELOPER
	#undef VI_USER
#endif

#ifdef _MSC_VER
	#if defined VI_EVERYWHERE
		#define VIPublicAPI 
	#elif defined VI_DEVELOPER
		#define VIPublicAPI __declspec(dllexport)
	#elif defined VI_USER
		#define VIPublicAPI __declspec(dllimport)
	#endif
#endif

#define VIPrivateAPI