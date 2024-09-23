#pragma once
#include "VIObject.h"
#include "VIConsole.h"

class VILoggerManager;
class VILoggerPrivate;
class VIMiCoreAPI VILogger :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;

	friend class VILoggerManager;
	friend class VILoggerPrivate;

	_Public enum class Level {
		Trace = VI_LOG_LEVEL_TRACE, Debug = VI_LOG_LEVEL_DEBUG, Info = VI_LOG_LEVEL_INFO,
		Warn = VI_LOG_LEVEL_WARN, Error = VI_LOG_LEVEL_ERROR, Fatal = VI_LOG_LEVEL_FATAL
	};
	_Public static QString LevelToString(Level level);

	Q_PROPERTY(Level level READ level WRITE setLevel);
	Q_PROPERTY(QString loggerName READ loggerName WRITE setLoggerName);

	_Public def_init VILogger(VISuper* parent = nullptr);
	_Public Level level() const;
	_Public void setLevel(const Level& level);
	_Public QString loggerName() const;
	_Public void setLoggerName(const QString& name);
	_Public void log(QString msg, Level level = Level::Info);
	_Public void trace(QString msg);
	_Public void debug(QString msg);
	_Public void info(QString msg);
	_Public void warn(QString msg);
	_Public void error(QString msg);
	_Public void fatal(QString msg);

	_Private VILoggerPrivate* d;
};