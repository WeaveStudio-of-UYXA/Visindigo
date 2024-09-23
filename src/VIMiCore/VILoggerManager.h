#pragma once
#include "VILogger.h"

class VILoggerManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;

	friend class VILogger;

	_Public static VILoggerManager* Instance(); 
	_Public def_init VILoggerManager(VISuper* parent = nullptr);
	_Public def_init ~VILoggerManager();
	_Public void start();
	_Public void setLoggerLevel(VILogger::Level level);
	_Public void setLogFolder(const QString& folder);
	_Public void setLogFileTimeFormat(const QString& format);
	_Public void setTimeFormat(const QString& format);
	_Public void setLogFormat(const QString& format);
	_Public void setLogFileMaxSize(quint32 bytes);
	_Public void setLogFileCacheSize(quint32 bytes);
	_Public VILogger* logger(const QString& name = "");
	_Protected void addLogger(VILogger* logger);
	_Protected void log(VILogger* logger, QString msg, VILogger::Level level);

	_Private class VILoggerManagerPrivate* d;
};