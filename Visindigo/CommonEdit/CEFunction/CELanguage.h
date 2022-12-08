#pragma once
#include <QtCore>
#ifndef TRUE
#define TRUE true
#define FALSE false
#endif

//This macro is used by CommonEdit Language Creator.
//CELC will ignore the "raw string" after CEL_TR that contains CELC_ESCAPE macro.
#define CELC_ESCAPE
#define CEL_TR(str) CE::CELanguage::Instance->returnValueOf(str)
#define CEL_VERSION 3

namespace CE {
	class CELanguage :public QObject {
		Q_OBJECT
	signals:
		void languageChanged();
	private:
		QMap<QString, QString> TransDict = {};
		QString DirPath = "";
	public:
		static CELanguage* Instance;
		CELanguage(QString FilePath = "") {
			DirPath = FilePath;
		}
		void setFilePath(QString FilePath) {
			DirPath = FilePath;
		}
		bool load() {
			QString TargetFileName = DirPath;
			QFile TargetFile;
			TargetFile.setFileName(TargetFileName);
			if (TargetFile.exists()) {
				if (TargetFile.isReadable()) {
					TargetFile.open(QIODevice::ReadOnly | QIODevice::Text);
					QTextStream TargetText(&TargetFile);
					TargetText.setCodec("UTF-8");
					while (TRUE) {
						if (TargetText.atEnd()) { break; }
						QString Line = TargetText.readLine();
						if (Line.isEmpty()) { continue; }
						if (Line[0] != '#' && Line[0] != '\n' && Line[0] != ' ') {
							if (!Line.contains(":")) {
								qDebug() << "Warning:CELanguage:The separator ':' was not checked on line ' " + Line + " ' in the file:" + TargetFileName;
								continue;
							}
							TransDict[Line.split(":")[0]] = Line.section(":", 0, -1);
						}
					}
					TargetFile.close();
					emit languageChanged();
					return TRUE;
				}
				else {
					qDebug() << "Error:CELanguage:The specified file '" + TargetFileName + "' is unreadable";
					return FALSE;
				}
			}
			else {
				qDebug() << "Error:CELanguage:The specified file '" + TargetFileName + "' could not be found";
				return FALSE;
			}
		}
		QString returnValueOf(QString Key) {
			if (TransDict.keys().contains(Key)) {
				return TransDict[Key];
			}
			else {
				qDebug() << "Error:CELanguage:The translated text corresponding to the key'" + Key + "' could not be found";
				return Key;
			}
		}
		void test() {
			CEL_TR("ATest");
		}
	};
}
