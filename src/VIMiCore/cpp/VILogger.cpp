#include "../VILogger.h"
#include "../VILoggerManager.h"

class VILoggerPrivate
{
	friend class VILogger;
	_Protected VILogger::Level Level = VILogger::Level(VI_LOG_LEVEL);
	_Protected QString LoggerName;
};

/*!
	\class VILogger
	\inmodule VIMiCore
	\since Visindigo 2.0.0
	\brief VILogger定义了Visindigo的日志记录器。

	VILogger定义了Visindigo的日志记录器，所有Visindigo的日志记录都应通过此类进行。
*/
/*!
	\enum VILogger::Level
	\since Visindigo 2.0.0
	\brief 定义了日志记录器的日志级别。

	定义了日志记录器的日志级别，包括Trace、Debug、Info、Warn、Error、Fatal。
*/ 
/*!
	\since Visindigo 2.0.0
	获取日志记录器的日志截止级别的字符串。
*/
QString VILogger::LevelToString(Level level)
{
	switch (level)
	{
	case Level::Trace:
		return "Trace";
	case Level::Debug:
		return "Debug";
	case Level::Info:
		return "Info";
	case Level::Warn:
		return "Warn";
	case Level::Error:
		return "Error";
	case Level::Fatal:
		return "Fatal";
	default:
		return "Unknown";
	}
}
/*!
	\property VILogger::level
	\brief 获取日志记录器的日志截止级别。
	\since Visindigo 2.0.0
	获取日志记录器的日志截止级别。小于此等级的日志将不会被记录。
*/
/*!
	\property VILogger::loggerName
	\brief 获取日志记录器的名称。
	\since Visindigo 2.0.0
	获取日志记录器的名称。
*/
/*!
	\since Visindigo 2.0.0
	\a parent 为VILogger的父对象。
	VILogger的默认构造函数
*/
def_init VILogger::VILogger(VISuper* parent) :VIObject(parent)
{
	d = new VILoggerPrivate();
	VILoggerManager::Instance()->addLogger(this);
}

/*!
	\since Visindigo 2.0.0
	获取日志记录器的日志截止级别。
*/
VILogger::Level VILogger::level() const
{
	return d->Level;
}

/*!
	\since Visindigo 2.0.0
	\a level 为要设置的日志截止级别。
	设置日志记录器的日志截止级别。
*/
void VILogger::setLevel(const Level& level)
{
	d->Level = level;
}

/*!
	\since Visindigo 2.0.0
	获取日志记录器的名称。
*/
QString VILogger::loggerName() const
{
	return d->LoggerName;
}
/*!
	\since Visindigo 2.0.0
	\a name 为要设置的日志记录器的名称。
	设置日志记录器的名称。
*/
void VILogger::setLoggerName(const QString& name)
{
	d->LoggerName = name;
}
/*!
	\since Visindigo 2.0.0
	\a msg 为要记录的日志信息。
	\a level 为要记录的日志级别。
	记录日志信息。
*/
void VILogger::log(QString msg, Level level)
{
	if (level >= d->Level)
	{
		VILoggerManager::Instance()->log(this, msg, level);
	}
}

/*!
	\since Visindigo 2.0.0
	\a msg 为要记录的日志信息。
	记录Trace级别的日志信息。
*/
void VILogger::trace(QString msg)
{
	log(msg, Level::Trace);
}

/*!
	\since Visindigo 2.0.0
	\a msg 为要记录的日志信息。
	记录Debug级别的日志信息。
*/
void VILogger::debug(QString msg)
{
	log(msg, Level::Debug);
}

/*!
	\since Visindigo 2.0.0
	\a msg 为要记录的日志信息。
	记录Info级别的日志信息。
*/
void VILogger::info(QString msg)
{
	log(msg, Level::Info);
}

/*!
	\since Visindigo 2.0.0
	\a msg 为要记录的日志信息。
	记录Warn级别的日志信息。
*/
void VILogger::warn(QString msg)
{
	log(msg, Level::Warn);
}

/*!
	\since Visindigo 2.0.0
	\a msg 为要记录的日志信息。
	记录Error级别的日志信息。
*/
void VILogger::error(QString msg)
{
	log(msg, Level::Error);
}

/*!
	\since Visindigo 2.0.0
	\a msg 为要记录的日志信息。
	记录Fatal级别的日志信息。
*/
void VILogger::fatal(QString msg)
{
	log(msg, Level::Fatal);
}



