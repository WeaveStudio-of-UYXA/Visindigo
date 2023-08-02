#pragma execution_character_set("utf-8") //所有含有const char的cpp文件都需要这一句（大概）
#include <VICore>
#include <VIWidgets>
#include "$safeprojectname$Package.h"

visindigo Program {
	VIFramework Frame(sysArgv);
	// 此处放置框架的初始化参数
	// VVVVVVVVVVVVVVVVVVVV
	Frame.useDebugModeRuntime();


	// AAAAAAAAAAAAAAAAAAA
	Frame.init(); // 初始化框架
	// 此处放置您的项目的初始化代码
	// VVVVVVVVVVVVVVVVVVVV
	VIConsole::printLine(VIConsole::inSuccessStyle("Hello world!"));
	LOAD_PACKAGE($safeprojectname$::Package);


	// AAAAAAAAAAAAAAAAAAA
	Frame.start(); // 启动框架，此行之后的代码将不会被执行
} ProgramEnd;