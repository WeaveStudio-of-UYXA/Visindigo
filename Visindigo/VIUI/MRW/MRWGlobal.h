#pragma once
#include "../../../Visindigo/VICore/VIGuiAnimation.h"
#include "../../../VIJSAPI/VIJSHost.h"
#define MRWAniProcess MRWGlobal::Process
#define MRWJSHost MRWGlobal::JSHost
#define MRWJSVIAPI MRWGlobal::JSHost->GUIHost
class MRWGlobal
{
public:
	static VIAnimationEventProcess* Process;
	static VIJSHost* JSHost;
	static QString VIProjectRootPath;
};