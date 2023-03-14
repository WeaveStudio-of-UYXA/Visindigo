#pragma execution_character_set("utf-8")

//#include "Visindigo/SPOL/SPOLSyntax.h"
#include "Visindigo/VIScene/TestBaseScene.h"
#include "Visindigo/VI2DScene/VI2DScene.h"
#include "Visindigo/VICore/VICore.h"
#include "UserCode/YSPMainPack/YSPMainPack.h"
void launchVisindigo2DTest() {
	VI2DWidget* w = new VI2DWidget();
#if VI_WINDOW == VI_WINDOW_SYS
	w->show();
#elif VI_WINDOW == VI_NO_WINDOW
	w->show();
#endif
}
void launchVisindigoSceneTest() {
#ifdef VI_USE_3D
	TestSceneView* w = new TestSceneView();
#if VI_WINDOW == VI_WINDOW_SYS
	w->show();
#elif VI_WINDOW == VI_NO_WINDOW
	w->show();
#endif
#endif
}
/*
void launchVisindigoSPOLItp() {
	QString code = "var name=1\"3\"";
	qDebug() << code;
	SPOLSyntax::escapeCharacterRestore(&code);
	qDebug() << SPOLSyntax::wordSplitter(code);
	QStringList fileCode = SPOLSyntax::loadCompleted("../../Visindigo/Dev/test");
	for (auto i = fileCode.begin(); i != fileCode.end(); i++) {
		qDebug() << SPOLSyntax::wordSplitterCompleted(*i);
	}
}*/
int main(int argc, char* argv[]) {
	VIFramework VIFrame(argc, argv);
	LOAD_PACKAGE(YSPMainPack);
	VIFrame.start();
	return VIFrame.getReturnCode();
}

//gBEHAVIOR->start();
	//launchVisindigoSPOLItp();
	//launchVisindigo2DTest();
	//launchVisindigoRuntime();