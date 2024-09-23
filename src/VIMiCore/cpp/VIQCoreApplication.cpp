#include "../VIQCoreApplication.h"
#include "../VIMiCoreFramework.h"
#include "../private/VIMiCoreFrameworkPrivate.h"
#include "../VIConsole.h"

/*!
	\class VIQCoreApplication
	\brief 对QCoreApplication的加壳，以便进行异常处理。
	\since Visindigo 2.0.0
	\sa VIQGuiApplication, VIQApplication
	此对象仅重载了notify()函数，以便进行异常处理。
*/
def_init VIQCoreApplication::VIQCoreApplication(int& argc, char** argv) :QCoreApplication(argc, argv)
{
}

/*!
	\since Visindigo 2.0.0
	重载了QApplication的notify()函数，以便进行异常处理。
*/
bool VIQCoreApplication::notify(QObject* receiver, QEvent* e)
{
	try
	{
		return QCoreApplication::notify(receiver, e);
	}
	catch (std::exception& e)
	{
		VIMiCoreFramework::Instance()->d->onException(e);
	}
	return false;
}