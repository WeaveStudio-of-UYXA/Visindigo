#include "../VIPackage.h"

class VIPackagePrivate
{
	friend class VIPackageManager;
	friend class VIPackage;
	_Protected QString UniqueName;
	_Protected QString Name;
	_Protected QMap<QString, const QMetaObject*> Classes;
	_Protected VIJsonDocument Config;
	_Protected VILogger* Logger;
};
/*!
	\class VIPackage
	\inmodule VIMiCore
	\brief VIPackage定义了Visindigo的功能集合。
	\since Visindigo 2.0.0

	VIPackage定义了Visindigo的功能集合，所有在C++或VisindigoJS中的功能集合都应利用此类进行封装。
	无论对于C++还是VisindigoJS，VIPackage都是一个抽象类，不能直接实例化。

	对于C++上构造的VIPackage，如果其需要在动态链接库中携带资源文件，则资源文件的路径被限定于\c {/package/包唯一名称}
	目录下。例如，包唯一名称为\c {com.visindigo.example}，则资源文件的路径应为\c {/package/com.visindigo.example}。
	\code
		QImage image(":/package/com.visindigo.example/image.png");
	\endcode

	内部qrc路径字符串在设置了唯一名称后，可以通过VIPackage::internalPath()获取，其是从冒号开始，斜杠结束的字符串。
	与其类似的是包的外部路径，即调用VIPackage::externalPath()获取的路径。这个路径是相对于Visindigo程序执行目录的。
	要知晓资源文件的绝对路径，可以调用VIPackage::absolutePath()获取。
*/
/*!
	\property VIPackage::uniqueName
	\brief 获取功能集合的唯一名称。
	\since Visindigo 2.0.0
	获取功能集合的唯一名称。
*/
/*!
	\property VIPackage::name
	\brief 获取功能集合的名称。
	\since Visindigo 2.0.0
	获取功能集合的名称。
*/
/*
	\typedef VisindigoDllMainPtr
	\relates VIPackage
	\brief 动态链接库的入口函数。
	\since Visindigo 2.0.0

	在用户使用C++编写Visindigo功能组件时，需要在动态链接库中导出一个函数，这个函数的返回值是VIPackage*，
	这个函数的名称\b{必须}为\b{VisindigoDllMain}。这个函数会在Visindigo加载动态链接库时被调用，例如
	\code
		extern "C" VIPackage* VisindigoDllMain()
		{
			return new MyPackage();
		}
	\endcode
	Visindigo不关心dll内部的实现，只要这个函数返回一个VIPackage*即可。
*/
/*!
	\since Visindigo 2.0.0
	\a parent 为VIPackage的父对象。
	VIPackage的默认构造函数
*/
def_init VIPackage::VIPackage(QString uniqueName, QObject* parent) :VIObject(parent)
{
	d = new VIPackagePrivate();
	d->UniqueName = uniqueName;
	d->Logger = new VILogger(this);
	d->Config.load(externalPath() + "config.json", internalPath() + "config.json");
}

/*!
	\since Visindigo 2.0.0
	获取包的唯一名称。
	一般来说，包的唯一名称形如"cn.yxgeneral.visindigo.micore"
	\note 注意这不是包的名称，请参见name()。
*/
QString VIPackage::uniqueName() const
{
	return d->UniqueName;
}

/*!
	\since Visindigo 2.0.0
	\a value 为要设置的唯一名称。
	设置包的唯一名称。
*/
void VIPackage::setUniqueName(const QString& value)
{
	d->UniqueName = value;
}

/*!
	\since Visindigo 2.0.0
	获取包的名称。
	一般来说，包的名称形如"MiCore"
	\note 注意这不是包的唯一名称，请参见uniqueName()。
*/
QString VIPackage::name() const
{
	return d->Name;
}

/*!
	\since Visindigo 2.0.0
	\a value 为要设置的名称。
	设置包的名称。
*/
void VIPackage::setName(const QString& value)
{
	d->Name = value;
}

/*!
	\since Visindigo 2.0.0
	\a className 为要检查的类名。
	返回包是否包含指定的类。
*/
bool VIPackage::packageContainsClass(const QString& className) const
{
	return d->Classes.contains(className);
}

/*!
	\since Visindigo 2.0.0
	\a metaObject 为要记录的类的元对象。
	记录一个类。
*/
void VIPackage::recordClass(const QMetaObject* metaObject)
{
	d->Classes[metaObject->className()] = metaObject;
}

/*!
	\since Visindigo 2.0.0
	返回包的内部路径。
	这是qrc规定的格式，此返回值从冒号开始，正斜杠结束，例如\c {:/package/cn.yxgeneral.visindigo.micore/}
*/
QString VIPackage::internalPath() const
{
	return QStringLiteral(":/package/%1/").arg(uniqueName());
}

/*!
	\since Visindigo 2.0.0
	返回包的外部路径。
	这是文件系统规定的格式，此返回值从正斜杠开始，正斜杠结束，例如\c {/package/cn.yxgeneral.visindigo.micore/}
*/

QString VIPackage::externalPath() const
{
	return QStringLiteral("/package/%1/").arg(uniqueName());
}

/*!
	\since Visindigo 2.0.0
	返回包的绝对路径。
	这是文件系统规定的格式，此返回值从盘符开始，正斜杠结束，例如\c {C:/visindigoProgram/package/cn.yxgeneral.visindigo.micore/}
*/
QString VIPackage::absolutePath() const
{
	return QCoreApplication::applicationDirPath() + externalPath();
}

/*!
	\since Visindigo 2.0.0
	返回包的配置文档。
*/
VIJsonDocument* VIPackage::config() const
{
	return &d->Config;
}

/*!
	\since Visindigo 2.0.0
	返回包的日志记录器。
*/
VILogger* VIPackage::logger() const
{
	return d->Logger;
}