#pragma once
/*
此文档解读vis文件中的include关键字，将全部vis文件合并为一个文件
此过程还处理如下内容：
1. 将所有的tab转换为4个空格
2. 将所有的行末反斜杠续写合并为一行。
*/
#include "../../VICore/macro/VIMarco.h"
#include <QtCore>
#include <exception>

class VISCFileReader :public QObject
{
	Q_OBJECT;
	_Private QString VISRootDir;
	_Private QString VISRootFileName;
	_Private QStringList VISFileList;
	_Private QByteArray VISFileContent;
	_Public def_init VISCFileReader(QObject* parent = VI_NULLPTR) :QObject(parent) {};
	_Public def_del ~VISCFileReader() {};
	_Public void readVISFile(QString fileDir, QString fileName) {
		VISRootFileName = fileName;
		VISRootDir = fileDir;
		qDebug() << VISRootFileName << VISRootDir;
		VISFileList.append(VISRootDir + "/" + VISRootFileName);
		try {
			readVISFile();
			//qDebug() << VISFileContent;
			VISFileContent.replace("\t", "    ");
			QFile file(VISRootDir + "/" + "__TOTAL__.vis");
			if (file.exists()) {
				file.remove();
			}
			if (!file.open(QIODevice::NewOnly | QIODevice::Text)) {
				throw std::exception("can not build __TOTAL__.vis file to save the code.");
			}
			QTextStream out(&file);
			out << VISFileContent;
		}
		catch (std::exception e) {
			qDebug().noquote() << "["+QTime::currentTime().toString("hh:mm:ss.zzz") + "] During the merge, an error occurred: ";
			qDebug() << e.what();
			qDebug() << "Code merge forced to terminate";
		}
	}
	_Private void readVISFile() {
		QFile file(VISFileList.last());
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			throw std::exception(QString("can not open the file: " + file.fileName()).toStdString().c_str());
		}
		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line = in.readLine();
			if (line.startsWith("include")) {
				QStringList includeList = line.split(" ");
				if (includeList.size() == 2) {
					QString filePath = VISRootDir + "/" + includeList[1].replace(".", "/") + ".vis";
					if (!VISFileList.contains(filePath)) {
						VISFileList.append(filePath);
						readVISFile();
					}
				}
				else {
					throw std::exception(QString("include error in file: "+ file.fileName()).toStdString().c_str());
				}
			}
			else {
				if (line.endsWith("\\")) {
					VISFileContent.append(line.left(line.size() - 1));
				}
				else {
					VISFileContent.append(line + "\n");
				}
			}
		}
	}
};