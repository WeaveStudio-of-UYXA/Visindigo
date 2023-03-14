#pragma once
#include "CommonEdit/CEFunction/CELanguage.h"
#include "Visindigo/VICore/macro/VIMarco.h"
#define WINDOWS_DEPLOY 1
#define ANDROID_DEPLOY 2

#define DEPLOY WINDOWS_DEPLOY

//#define VI_USE_3D

#define VI_WINDOW_SYS 1
#define VI_NO_WINDOW 2
#if DEPLOY == ANDROID_DEPLOY
#define VI_WINDOW VI_NO_WINDOW
#elif DEPLOY == WINDOWS_DEPLOY
#define VI_WINDOW VI_WINDOW_SYS
#endif
