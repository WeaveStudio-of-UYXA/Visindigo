#pragma once
#include "VIObject.h"
#include "VIConsole.h"

class VIDocument :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIDocument() {
	}
	_Public static QString getWorkingPath() { return QDir::currentPath(); }
	_Public static QString getProgramPath() { return QCoreApplication::applicationDirPath(); }
	_Public static QString getHomePath() { return QDir::homePath(); }
	_Public static QString getUserName() { return QDir::home().dirName(); }
	_Public static QString getTempPath() { return QDir::tempPath(); }
	_Public static QString getRootPath() { return QDir::rootPath(); }
	_Public static QString getDesktopPath() { return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation); }
	_Public static QString getDocumentsPath() { return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation); }
	_Public static QString getDownloadPath() { return QStandardPaths::writableLocation(QStandardPaths::DownloadLocation); }
	_Public static QString getMusicPath() { return QStandardPaths::writableLocation(QStandardPaths::MusicLocation); }
	_Public static QString getMoviesPath() { return QStandardPaths::writableLocation(QStandardPaths::MoviesLocation); }
	_Public static QString getPicturesPath() { return QStandardPaths::writableLocation(QStandardPaths::PicturesLocation); }
	_Public static QString getApplicationsPath() { return QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation); }
	_Public static QString getFontsPath() { return QStandardPaths::writableLocation(QStandardPaths::FontsLocation); }
	_Public static QString getCachePath() { return QStandardPaths::writableLocation(QStandardPaths::CacheLocation); }
};

class VILanguageDoc :public VIObject
{
	_Public typedef QHash<QString, QString> TranslationsTable;
	Q_OBJECT;
	VI_OBJECT;
	_Private TranslationsTable Translations;
	_Private QString FilePath;
	_Private QString LanguageName;
	_Private bool Loaded = false;
	_Public def_init VILanguageDoc(QString filePath = "", VISuper* parent = VI_NULLPTR) :VIObject(parent) {
		FilePath = filePath;
	}
	_Public bool load() {
		return loadFrom(FilePath);
	}
	_Public bool loadFrom(QString path, bool append = false, bool _override = false) {
		if (path == "") { return false; }
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { return false; }
		FilePath = path;
		LanguageName = path.section("/", -1, -1).section(".", 0, -1);
		if (!append) { Translations.clear(); }
		QTextStream in(&file);
		in.setCodec("utf-8");
		QString line;
		while (!in.atEnd()) {
			line = in.readLine();
			if (line == "") { continue; }
			if (line.startsWith("#") || line.startsWith("//") || line.startsWith(" ")) { continue; }
			parseLine(line, _override);
		}
		file.close();
		Loaded = true;
		return true;
	}
	_Private void parseLine(QString line, bool _override) {
		QString key = line.section(":", 0, 0);
		QString value = line.section(":", 1, -1);
		if (Translations.contains(key)) {
			if (_override) {
				Translations[key] = value;
			}
			else {
				VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Encountered redefined key: " + key + ", Redefining content ignored."));
			}
		}
		else {
			Translations.insert(key, value);
		}
	}
	_Public QString translate(QString key) {
		if (Translations.contains(key)) {
			return Translations[key];
		}
		else {
			return key;
		}
	}
	_Public QString getLanguageName() { return LanguageName; }
	_Public bool isLoaded() { return Loaded; }
};