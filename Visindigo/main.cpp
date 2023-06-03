#pragma execution_character_set("utf-8")
#include "Visindigo/VICore/VICore.h"
#include "UserCode/YSPMainPack/YSPMainPack.h"

visindigo program
{
	VIFramework VIFrame(sysArgv);
	VIFrame.useDebugModeRuntime();
	VIFrame.init();
	LOAD_PACKAGE(YSPMainPack);
	VIFrame.start();
}
programEnd