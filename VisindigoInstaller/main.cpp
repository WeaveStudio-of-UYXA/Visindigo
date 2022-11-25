#pragma execution_character_set("utf-8")
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "UI/Installer.h"
#include "API/FileMetaData.h"
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	API::FileMetaData::MetaDataList OldList = API::FileMetaData::getAllFilesMD5FromFolder("E:/source/repos/Visindigo/x64/Visindigo");
	API::FileMetaData::removeRootPath("E:/source/repos/Visindigo/x64/Visindigo", &OldList);
	API::FileMetaData::createMetaDataFile(OldList, "E:/source/repos/Visindigo/x64/metainfo.txt");
	API::FileMetaData::MetaDataList NewList = API::FileMetaData::loadMetaDataFromFile("E:/source/repos/Visindigo/x64/metanew.txt");
	API::FileMetaData::ChangeDataList ChangeList = API::FileMetaData::analysisChange(OldList, NewList);
	API::FileMetaData::createChangeDataFile(ChangeList, "E:/source/repos/Visindigo/x64/changedata.txt");
	qDebug() << "NONe";
	VisindigoMainWin* mainWin = new VisindigoMainWin();
	mainWin->show();
	return app.exec();
}