#pragma once
#include <QtCore>

namespace API {
	class FileMetaData :public QObject
	{
		Q_OBJECT
		struct MetaData {
			QString MD5;
			QString FilePath;
		};
	public:
		static MetaData GetFileMD5(QString FilePath) {
			QFile File(FilePath);
			if (!File.open(QIODevice::ReadOnly)) {
				qDebug() << "File open failed";
				return MetaData();
			}
			QCryptographicHash Hash(QCryptographicHash::Md5);
			if (!Hash.addData(&File)) {
				qDebug() << "Hash add data failed";
				return MetaData();
			}
			File.close();
			return MetaData{ Hash.result().toHex(),FilePath };
		}
		static QFileInfoList getAllFilesInFolder(QString FolderPath) {

			QDir Dir(FolderPath);
			if (!Dir.exists()) {
				qDebug() << "Folder not exists";
				return QFileInfoList();
			}
			Dir.setFilter(QDir::Files | QDir::NoSymLinks);
			QFileInfoList list = Dir.entryInfoList();
			Dir.setFilter(QDir::NoFilter);
			foreach(QString subDir, Dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
				//若存在子目录，则递归调用sizeOf函数
				list += getAllFilesInFolder(FolderPath + QDir::separator() + subDir);
			return list;
		}
		static QList<MetaData> GetAllFileMD5FromFolder(QString FolderPath) {
			QList<MetaData> Result;
			QFileInfoList list = getAllFilesInFolder(FolderPath);
			for (int i = 0; i < list.size(); ++i) {
				QFileInfo fileInfo = list.at(i);
				Result.append(GetFileMD5(fileInfo.absoluteFilePath()));
			}
			return Result;
		}
		static void createMetaDataFile(QString FolderPath, QString FileName) {
			QList<MetaData> MetaDataList = GetAllFileMD5FromFolder(FolderPath);
			QFile File(FileName);
			if (!File.open(QIODevice::WriteOnly | QIODevice::Text)) {
				qDebug() << "File open failed";
				return;
			}
			for (auto i = MetaDataList.begin(); i != MetaDataList.end(); ++i) {
				File.write(i->FilePath.toUtf8() +" "+ i->MD5.toUtf8() + "\n");
			}
			File.close();
		}
	};
}