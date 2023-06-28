#pragma execution_character_set("utf-8")
#include "VICore/VICore.h"

/*
* Visindigo Main
* Every Visindigo program must start with "visindigo program" and end with "programEnd"
*/
visindigo program {
	VIFramework VIFrame(sysArgv);
	// You can put your framework initialization code here
	// ##########################################VVVVVVVVVVVVVVVVVVVV
	VIFrame.useDebugModeRuntime();


	// ##########################################AAAAAAAAAAAAAAAAAAA
	// Here we initialize the framework
	VIFrame.init();

	// You can put your own code here
	// ##########################################VVVVVVVVVVVVVVVVVVVV


	// ##########################################AAAAAAAAAAAAAAAAAAA
	// Here we start the framework
	VIFrame.start();
	// Any code after this line will not be executed
} programEnd;