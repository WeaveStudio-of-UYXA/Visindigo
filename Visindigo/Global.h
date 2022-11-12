#pragma once
#define WINDOWS_DEPLOY

#ifdef WINDOWS_DEPLOY
#define DEPLOY 1
#endif
#ifdef ANDROID_DEPLOY
#define DEPLOY 2
#endif