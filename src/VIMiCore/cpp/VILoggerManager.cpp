#include "../VILoggerManager.h"
#include "../VILogger.h"

class VILoggerManagerPrivate
{
	friend class VILoggerManager;
	_Protected static VILoggerManager* Instance;
	_Protected QMap<QString, VILogger*> Loggers;
	_Protected VILogger* DefaultLogger = nullptr;
	_Protected VILogger::Level Level = VILogger::Level(VI_LOG_LEVEL);
	_Protected QString LogFolder;
	_Protected QString LogFileTimeFormat = "yy_MM_dd_hh_mm_ss";
	_Protected QString TimeFormat = "hh:mm:ss";
	_Protected QString LogFormat = "[%{time}][%{level}][%{logger}]: %{msg}";
	_Protected QFile* LogFile = nullptr;
	_Protected QTextStream* LogStream = nullptr;
	_Protected quint32 LogFileMaxSize = 1024 * 1024 * 10; // 10MB
	_Protected quint32 LogFileCacheSize = 128; // 128B
	_Private quint32 cacheSize = 0;
	_Private quint32 totalSize = 0;
	_Protected void start();
	_Private void addLog(QString log);
};

VILoggerManager* VILoggerManagerPrivate::Instance = nullptr;

void VILoggerManagerPrivate::start() {
	if (LogFile != nullptr) {
		LogStream->flush();
		LogFile->close();
		delete LogStream;
		delete LogFile;
	}
	//check file exist
	quint16 retry = 0;
	QString FileName = LogFolder + "/" + QDateTime::currentDateTime().toString(LogFileTimeFormat) +
		"_" + QString::number(retry) + ".log";
	while (QFile::exists(FileName)) {
		retry++;
		FileName = LogFolder + "/" + QDateTime::currentDateTime().toString(LogFileTimeFormat) +
			"_" + QString::number(retry) + ".log";
		if (retry > 100) {
			qDebug() << "Can't create log file!";
			return;
		}
	}
	LogFile = new QFile(FileName);
	LogFile->open(QIODevice::NewOnly | QIODevice::Text | QIODevice::Append);
	LogStream = new QTextStream(LogFile);
}

void VILoggerManagerPrivate::addLog(QString log) {
	qint64 size = log.size();
	totalSize += size;
	*LogStream << log << "\n";
	LogStream->flush();
	cacheSize = 0;
	if (totalSize >= LogFileMaxSize) {
		totalSize = 0;
		start();
	}
}
/*!
	\class VILoggerManager
	\inmodule VIMiCore
	\since Visindigo 2.0.0
	\brief VILoggerManager定义了Visindigo的日志记录器管理器。

	VILoggerManager定义了Visindigo的日志记录器管理器，所有Visindigo的日志记录器都应通过此类进行管理。
*/
/*!
	\since Visindigo 2.0.0
	\a parent 为VILoggerManager的父对象。
	VILoggerManager的默认构造函数
*/
def_init VILoggerManager::VILoggerManager(VISuper* parent) :VIObject(parent) {
	if (VILoggerManagerPrivate::Instance!=nullptr) {
		qDebug() << "VILoggerManager has been created!";
		abort();
	}
	VILoggerManagerPrivate::Instance = this;
	d = new VILoggerManagerPrivate();
	d->DefaultLogger = new VILogger(this);
	d->DefaultLogger->setLoggerName("Global");
	d->DefaultLogger->setLevel(d->Level);
	d->LogFolder = QDir::currentPath() + "/logs";
	QDir dir(d->LogFolder);
	if (!dir.exists()) {
		dir.mkpath(d->LogFolder);
	}
}

/*!
	\since Visindigo 2.0.0
	VILoggerManager的析构函数
*/
def_init VILoggerManager::~VILoggerManager() {
	delete d->DefaultLogger;
	d->LogStream->flush();
	d->LogFile->close();
	delete d->LogStream;
	delete d->LogFile;
	delete d;
}

/*!
	\since Visindigo 2.0.0
	启动日志记录器管理器。
*/
void VILoggerManager::start() {
	d->start();
}
/*!
	\since Visindigo 2.0.0
	\return 返回VILoggerManager的实例。
	获取VILoggerManager的实例。
*/
VILoggerManager* VILoggerManager::Instance() {
	return VILoggerManagerPrivate::Instance;
}

/*!
	\since Visindigo 2.0.0
	\a level 为要设置的日志截止级别。
	设置全局日志截止级别，小于此等级的日志将不会被记录。全局截止级别在日志截止级别之后判定，
	也就是说，如果全局截止级别为Info，日志截止级别为Debug，则Debug级别的日志虽然能通过
	日志截止级别的判定，但是在全局截止级别的判定中将被过滤掉。
*/
void VILoggerManager::setLoggerLevel(VILogger::Level level) {
	d->Level = level;
}

/*!
	\since Visindigo 2.0.0
	\a folder 为要设置的日志文件夹。
	设置日志文件夹，日志文件将会被保存在这个文件夹下。
*/
void VILoggerManager::setLogFolder(const QString& folder) {
	d->LogFolder = folder;
}

/*!
	\since Visindigo 2.0.0
	\a format 为要设置的日志文件时间格式。
	设置日志文件时间格式，日志文件的时间格式将会按照这个格式进行命名。
*/
void VILoggerManager::setLogFileTimeFormat(const QString& format) {
	d->LogFileTimeFormat = format;
}

/*!
	\since Visindigo 2.0.0
	\a format 为要设置的时间格式。
	设置时间格式，日志记录器将会按照这个格式记录时间。
*/
void VILoggerManager::setTimeFormat(const QString& format) {
	d->TimeFormat = format;
}

/*!
	\since Visindigo 2.0.0
	\a format 为要设置的日志格式。
	设置日志格式，日志记录器将会按照这个格式记录日志。
*/
void VILoggerManager::setLogFormat(const QString& format) {
	d->LogFormat = format;
}

/*!
	\since Visindigo 2.0.0
	\a bytes 为要设置的日志文件最大大小。
	设置日志文件最大大小，当日志文件大小超过这个值时，将会新建一个日志文件。
*/
void VILoggerManager::setLogFileMaxSize(quint32 bytes) {
	d->LogFileMaxSize = bytes;
}

/*!
	\since Visindigo 2.0.0
	\a bytes 为要设置的日志文件写入缓冲区大小。
	设置日志文件写入缓冲区大小，当缓冲区大小超过这个值时，将会触发一次写入操作。
*/
void VILoggerManager::setLogFileCacheSize(quint32 bytes) {
	d->LogFileCacheSize = bytes;
}
/*!
	\since Visindigo 2.0.0
	\a name 为要获取的日志记录器的名称。
	\return 返回指定名称的日志记录器。
	获取指定名称的日志记录器，如果不存在则会返回默认日志记录器。
*/
VILogger* VILoggerManager::logger(const QString& name) {
	if (d->Loggers.contains(name)) {
		return d->Loggers[name];
	}
	else {
		return d->DefaultLogger;
	}
}

/*!
	\since Visindigo 2.0.0
	\a logger 为要添加的日志记录器。
	添加日志记录器。
*/
void VILoggerManager::addLogger(VILogger* logger) {
	d->Loggers[logger->loggerName()] = logger;
}

/*!
	\since Visindigo 2.0.0
	\a logger 为要记录的日志记录器。
	\a msg 为要记录的日志信息。
	\a level 为要记录的日志级别。
	记录日志信息。
*/
void VILoggerManager::log(VILogger* logger, QString msg, VILogger::Level level) {
	if (level < d->Level) {
		return;
	}
	QString rawText = VIConsole::getRawText(msg);
	switch (level) {
	case VILogger::Level::Info:
		msg = VIConsole::inNoticeStyle(msg);
		break;
	case VILogger::Level::Warn:
		msg = VIConsole::inWarningStyle(msg);
		break;
	case VILogger::Level::Error:
		msg = VIConsole::inErrorStyle(msg);
		break;
	case VILogger::Level::Fatal:
		msg = VIConsole::inErrorStyle(msg);
		break;
	}
	QString log = d->LogFormat;
	log = log.replace("%{time}", QDateTime::currentDateTime().toString(d->TimeFormat))
		.replace("%{level}", VILogger::LevelToString(level))
		.replace("%{logger}", logger->loggerName());
	QString consoleLog = log;
	consoleLog = consoleLog.replace("%{msg}", msg);
	QString fileLog = log.replace("%{msg}", rawText);
	d->addLog(fileLog);
	VIConsole::print(consoleLog);
}