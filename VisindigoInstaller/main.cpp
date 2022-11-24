#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "UI/Installer.h"
#include "API/FileMetaData.h"
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	API::FileMetaData::createMetaDataFile("E:/source/repos/Visindigo/x64/Visindigo", "E:/source/repos/Visindigo/x64/metainfo.txt");
	VisindigoMainWin* mainWin = new VisindigoMainWin();
	mainWin->show();
	return app.exec();
}