#include "../VIMiCoreFramework.h"
#include "../private/VIMiCoreFrameworkPrivate.h"
#include "../VIQCoreApplication.h"
#include "../VILoggerManager.h"

VIMiCoreFramework* VICoreFrameworkPrivate::Instance = nullptr;

bool VICoreFrameworkPrivate::onException(const std::exception& e)
{
	qDebug() << "Exception: " << e.what();
	return false;
}
/*!
	\class VICoreFramework
	\brief 此类在Visindigo应用中与QCoreApplication处于类似位置
	\since Visindigo 2.0.0
	\inmodule VIMiCore
*/
/*!
	\since Visindigo 2.0.0
	\a argc 命令行参数个数
	\a argv 命令行参数
	用法与QCoreApplication的构造函数相同
*/
VIMiCoreFramework::VIMiCoreFramework(int& argc, char** argv)
{
	if (VICoreFrameworkPrivate::Instance != nullptr)
	{
		qDebug() << "VICoreFramework instance already exists!";
		abort(); 
	}
	VICoreFrameworkPrivate::Instance = this;
	d = new VICoreFrameworkPrivate();
	d->VIQAppInstance = new VIQCoreApplication(argc, argv);
	d->LoggerManager = new VILoggerManager(this);
}
/*!
	\since Visindigo 2.0.0
	VICoreFramework的析构函数
*/
VIMiCoreFramework::~VIMiCoreFramework()
{
	delete d;
}
/*!
	\since Visindigo 2.0.0
	\return 返回VICoreFramework的实例
*/
VIMiCoreFramework* VIMiCoreFramework::Instance()
{
	return VICoreFrameworkPrivate::Instance;
}
/*!
	\since Visindigo 2.0.0
	\return 返回日志记录器实例
*/
VILogger* VIMiCoreFramework::logger(const QString& name)
{
	return d->LoggerManager->logger(name);
}
/*!
	\since Visindigo 2.0.0
	设置日志记录器的全局日志级别
*/
void VIMiCoreFramework::setLoggerLevel(VILogger::Level level)
{
	d->LoggerManager->setLoggerLevel(level);
}
/*!
	\since Visindigo 2.0.0
	在完成初始参数的设置后调用此函数，以提示Visindigo进入初始化状态
*/
void VIMiCoreFramework::init()
{
	d->LoggerManager->start();
}
/*!
	\since Visindigo 2.0.0
	在初始化完成后调用此函数，以启动Visindigo应用	
*/
void VIMiCoreFramework::exec()
{
	qApp->exec();
}