#pragma once
//编译导出选项
//使用Debug、Release编译时，预置VI_EVERYWHERE
//使用DllDebug、DllRelease编译时，预置VI_DEVELOPER
//上述两种情况都不是时，预置VI_USER
#define VI_USER
#ifdef VI_CORE_EXPORT
#undef VI_USER
#endif
#ifdef VI_CORE_DEVELOPER
#undef VI_USER
#endif
#ifdef VI_USER
#endif

#ifdef _MSC_VER
#if defined VI_CORE_DEVELOPER
#define VICoreAPI
#elif defined VI_CORE_EXPORT
#define VICoreAPI __declspec(dllexport)
#elif defined VI_USER
#define VICoreAPI __declspec(dllimport)
#endif
#else
#define VICoreAPI
#endif
