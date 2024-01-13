#pragma once
#include "VIObject.h"

#define VI_ENUMSTR(enumName, enumValue) case enumName::enumValue: return #enumValue;
class VIPublicAPI VIPathInfo {
	VI_STATIC_CLASS(VIPathInfo);
	_Public static QString getWorkingPath() { return QDir::currentPath(); }
	_Public static QString getPackageRootPath() { return QCoreApplication::applicationDirPath() + "/package"; }
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
	_Public static qint64 getSizeOf(const QString& path);
	_Public static QString getCountingUnitStr(Visindigo::CountingUnit c);
	_Public static QString getReadableSize(double rawSize, Visindigo::BinarySizeUnit u = Visindigo::Byte, Visindigo::CountingUnit c = Visindigo::_0, Visindigo::BinarySizeFormat f = Visindigo::IEC);
	_Public static void openExplorer(const QString& path);
	_Public static void openBrowser(const QString& url);
};
