#pragma once
//此项目控制部署目标平台
//#define LINUX_DEPLOY //暂时不支持
//#define ANDROID_DEPLOY //arm64-v8a
//#define ANDROID_DEPLOY_OLD //armeabi-v7a
//#define WINDOWS_DEPLOY_32 //x86_32
#define WINDOWS_DEPLOY //x86_64

#define VI_LOG_LEVEL_TRACE 1000
#define VI_LOG_LEVEL_DEBUG 2000
#define VI_LOG_LEVEL_INFO 3000
#define VI_LOG_LEVEL_WARN 4000
#define VI_LOG_LEVEL_ERROR 5000
#define VI_LOG_LEVEL_FATAL 6000

//编译导出选项
//使用Debug、Release编译时，预置VI_EVERYWHERE
//使用DllDebug、DllRelease编译时，预置VI_DEVELOPER
//上述两种情况都不是时，预置VI_USER
#define VI_USER
#ifdef VI_MICORE_EXPORT
#define VI_LOG_LEVEL VI_LOG_LEVEL_TRACE
#undef VI_USER
#endif
#ifdef VI_MICORE_DEVELOPER
#define VI_LOG_LEVEL VI_LOG_LEVEL_TRACE
#undef VI_USER
#endif
#ifdef VI_USER
#define VI_LOG_LEVEL VI_LOG_LEVEL_INFO
#endif

#ifdef _MSC_VER
#if defined VI_MICORE_DEVELOPER
#define VIMiCoreAPI
#elif defined VI_MICORE_EXPORT
#define VIMiCoreAPI __declspec(dllexport)
#elif defined VI_USER
#define VIMiCoreAPI __declspec(dllimport)
#endif
#else
#define VIPublicAPI
#endif

#define VIPrivateAPI

#define __AUX_STR_EXP(_exp_) #_exp_
#define ___AUX_STR(_exp_) __AUX_STR_EXP(_exp_)
#define __LOCATION_STR __FILE__ "("  ___AUX_STR(__LINE__) ")"

#define throw_warning(_code_, _message_) message(__LOCATION_STR ": warning C" ___AUX_STR(_code_) ": " _message_)
#define throw_error(_level_, _code_, _message_) message(__LOCATION_STR ":" _level_ " error C" ___AUX_STR(_code_) ": " _message_)
