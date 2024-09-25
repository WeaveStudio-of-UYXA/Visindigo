#pragma execution_character_set("utf-8")
#include <VIMiCoreFramework.h>
int main(int argc, char *argv[])
{
	VIMiCoreFramework framework(argc, argv);
	framework.init();
	framework.logger()->info("Hello, World!");
	framework.exec();
}
