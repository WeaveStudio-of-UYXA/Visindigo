#pragma once

#define SPOL_IMP_NAME "YSP"
#define SPOL_VERSION_STR "10X"
#define SPOL_METHOD_NAME SPOL_IMP_NAME "." SPOL_VERSION_STR "."
#define YSP_Speaking SPOL_METHOD_NAME "Speaking"
#define YSP_Image SPOL_METHOD_NAME "Image" //包括旧版的立绘、背景，主要指这些的状态切换
#define YSP_Sound SPOL_METHOD_NAME "Sound"
#define YSP_AnyText SPOL_METHOD_NAME "AnyText"
#define YSP_StateChange SPOL_METHOD_NAME "StateChange" //包括旧版的前景切换、素材动画等