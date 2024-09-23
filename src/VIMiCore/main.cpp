#include "VIMiCore.h"
#include <exception>

#ifdef VI_MICORE_DEVELOPER
int main(int argc, char *argv[])
{
    VIMiCoreFramework a(argc, argv);
	a.init();
    //print current path
	VIConsole::print("Current Path: " + QDir::currentPath());
	QFile jsonFile("test.json");
	if (jsonFile.open(QIODevice::ReadOnly)) {
		QByteArray data = jsonFile.readAll();
		jsonFile.close();
		VIJsonConfig config;
		config.parse(data);
		VIConsole::print("Config:" + config.getString("Dependencies.0.Name"));
		VIConsole::print("Config:" + config.getString("Dependencies.0.Name"));
		VIConsole::print(QString::number(QDateTime::currentMSecsSinceEpoch()));
		config.setString("Dependencies.0.Name", QString::number(QDateTime::currentMSecsSinceEpoch()));
		VIConsole::print("Config:" + config.getString("Dependencies.0.Name"));
	}
	a.logger()->log("Hello World!");
	return a.exec();
}
#endif