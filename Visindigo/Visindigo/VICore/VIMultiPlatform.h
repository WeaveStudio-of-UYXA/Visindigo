#pragma once
#include "VIObject.h"
class VIMultiPlatform : public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIMultiPlatform(QObject* parent = VI_NULLPTR) :VIObject(parent) {};
	_Public static void exit() { QCoreApplication::exit(); }
	_Public static QString getSystemName() { return QSysInfo::prettyProductName(); }
	_Public static QString getSystemType() { return QSysInfo::productType(); }
	_Public static QString getSystemVersion() { return QSysInfo::productVersion(); }
	_Public static QStringList argv() { return qApp->arguments(); }
	_Public static QString getBuildAbi() { return QSysInfo::buildAbi(); }
	_Public static QString getCPUBuildType() { return QSysInfo::buildCpuArchitecture(); }
	_Public static QString getCPUCurrentType() { return QSysInfo::currentCpuArchitecture(); }
	_Public static QString getSystemKernelType() { return QSysInfo::kernelType(); }
	_Public static QString getSystemKernelVersion() { return QSysInfo::kernelVersion(); }
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