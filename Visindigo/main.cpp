#pragma execution_character_set("utf-8")

#include "Visindigo/VICore/VICore.h"
#include "UserCode/YSPMainPack/YSPMainPack.h"

int main(int argc, char* argv[]) {
	VIFramework VIFrame(argc, argv);
	LOAD_PACKAGE(YSPMainPack);
	VIFrame.start();
	return VIFrame.getReturnCode();
}
