#pragma once
#include <QtCore>
//问问工作室这玩意是不是应该加入CommonEdit而不是在这里待着
namespace API {
	class FileMetaData :public QObject
	{
		Q_OBJECT
	public:
		struct MetaData {
			QString MD5;
			QString FilePath;
		};
		enum class ChangeState {
			Delete,
			New,
			Update
		};
		struct ChangeData {
			ChangeState State;
			MetaData Meta;
		};
		typedef QList<MetaData> MetaDataList;
		typedef QList<ChangeData> ChangeDataList;
	public:
		static MetaData getFileMD5(QString FilePath) {
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
			foreach(QString subDir, Dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
				list += getAllFilesInFolder(FolderPath + QDir::separator() + subDir);
			}
			return list;
		}
		static MetaDataList getAllFilesMD5FromFolder(QString FolderPath) {
			QList<MetaData> Result;
			QFileInfoList list = getAllFilesInFolder(FolderPath);
			for (int i = 0; i < list.size(); ++i) {
				QFileInfo fileInfo = list.at(i);
				Result.append(getFileMD5(fileInfo.absoluteFilePath()));
			}
			return Result;
		}
		static void createMetaDataFile(MetaDataList MetaDataList, QString FileName) {
			QFile File(FileName);
			if (!File.open(QIODevice::WriteOnly | QIODevice::Text)) {
				qDebug() << "File open failed";
				return;
			}
			for (auto i = MetaDataList.begin(); i != MetaDataList.end(); ++i) {
				File.write(i->FilePath.toUtf8() +"||"+ i->MD5.toUtf8() + "\n");
			}
			File.close();
		}
		static MetaDataList loadMetaDataFromFile(QString FileName) {
			QList<MetaData> MetaList;
			QFile File(FileName);
			if (!File.open(QIODevice::ReadOnly | QIODevice::Text)) {
				qDebug() << "File open failed";
				return MetaDataList();
			}
			QTextStream Text(&File);
			Text.setCodec("UTF-8");
			QString Line;
			while (true) {
				if (Text.atEnd()) { break; }
				Line = Text.readLine();
				QStringList List = Line.split("||");
				qDebug() << List;
				MetaList.append(MetaData{ List[1],List[0] }); 
				//注意：metaData和changeData文档对于meta的保存顺序是FileName-MD5，与构造正好相反
			}
			File.close();
			return MetaList;
		}
		static void removeRootPath(QString RootPath, MetaDataList* List) {
			for (auto i = List->begin(); i != List->end(); i++) {
				i->FilePath.replace(RootPath, ".");
			}
		}
		static ChangeDataList analysisChange(MetaDataList MetaListLocal, MetaDataList MetaListLatest) {
			QList<ChangeData> rtn;
			for (auto i = MetaListLocal.begin(); i != MetaListLocal.end(); i++) {
				auto j = MetaListLatest.begin();
				int d = 0;
				while (true) {
					if ((* i).FilePath == ( * j).FilePath) {
						if ((*i).MD5 != (*j).MD5) {
							rtn.append(ChangeData{ ChangeState::Update, (*j) });
						}
						MetaListLatest.removeAt(d);
						break;
					}
					j++;
					d++;
					if (j == MetaListLatest.end()) {
						rtn.append(ChangeData{ ChangeState::Delete, (*i) });
						break; 
					}
				}
			}
			for (auto k = MetaListLatest.begin(); k != MetaListLatest.end(); k++) {
				rtn.append(ChangeData{ ChangeState::New, (*k) });
			}
			return rtn;
		}
		static void createChangeDataFile(ChangeDataList ChangeList, QString FileName) {
			QFile File(FileName);
			if (!File.open(QIODevice::WriteOnly | QIODevice::Text)) {
				qDebug() << "File open failed";
				return;
			}
			for (auto i = ChangeList.begin(); i != ChangeList.end(); ++i) {
				QString state = "E";
				switch (i->State) {
				case ChangeState::Delete:
					state = "D";
					break;
				case ChangeState::New:
					state = "N";
					break;
				case ChangeState::Update:
					state = "U";
					break;
				}
				File.write(state.toUtf8() + "||" + i->Meta.FilePath.toUtf8() + "||" + i->Meta.MD5.toUtf8() + "\n");
			}
			File.close();
		}
	};
}