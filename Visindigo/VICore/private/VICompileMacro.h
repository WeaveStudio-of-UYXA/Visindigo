#pragma once
//此项目控制部署目标平台
//#define LINUX_DEPLOY //暂时不支持
//#define ANDROID_DEPLOY //arm64-v8a
//#define ANDROID_DEPLOY_OLD //armeabi-v7a
//#define WINDOWS_DEPLOY_32 //x86_32
#define WINDOWS_DEPLOY //x86_64

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
#else
#define VIPublicAPI
#endif

#define VIPrivateAPI