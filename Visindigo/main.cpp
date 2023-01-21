#pragma execution_character_set("utf-8")
#include "init.h"
#include "Visindigo/SPOL/SPOLSyntax.h"

void launchVisindigoRuntime() {
	VIRuntimeWindow* w = new VIRuntimeWindow();
#if VI_WINDOW == VI_WINDOW_SYS
	w->showFullScreen();
#elif VI_WINDOW == VI_NO_WINDOW
	w->show();
#endif
}

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	doQRegisterMetaType();
	QString code = "var name=1\"3\"";
	qDebug() << code;
	SPOLSyntax::escapeCharacterRestore(&code);
	qDebug()<< SPOLSyntax::wordSplitter(code);
	//launchVisindigoRuntime();
	return app.exec();
}

