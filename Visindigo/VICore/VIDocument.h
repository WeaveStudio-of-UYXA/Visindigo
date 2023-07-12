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

