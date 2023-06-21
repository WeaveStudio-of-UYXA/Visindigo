#pragma execution_character_set("utf-8")
#include "VICore/VICore.h"


visindigo program
{
	VIFramework VIFrame(sysArgv);
	VIFrame.useDebugModeRuntime();
	VIFrame.init();

	VIFrame.start();
}
programEnd