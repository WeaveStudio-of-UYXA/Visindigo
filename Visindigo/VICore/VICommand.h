#pragma once
#include "VIObject.h"
#include "VIConsole.h"

typedef QMap<QString, QString> QStringMap;
class VIPublicAPI VICommandHost;
class VIPublicAPI VICommandHandler {
	friend class VICommandHost;
	VI_ProtectedProperty(QString, CommandName);
	VI_ProtectedProperty(QStringMap, NamedArgs);
	VI_ProtectedProperty(QStringList, UnnamedArgs);
	VI_ProtectedProperty(QString, CommandOutput);
	_Public virtual bool handleCommand() PureVirtual;
	_Public void debugPrint() {
		qDebug() << "CommandName:" << CommandName;
		qDebug() << "NamedArgs:" << NamedArgs;
		qDebug() << "UnnamedArgs:" << UnnamedArgs;
	}
	_Public def_init VICommandHandler();
	_Public def_del ~VICommandHandler();
};

#define VICommand_Reg(Name) new Name()
#define VICommand_Handler(Name) class VIPublicAPI Name :public VICommandHandler { _Public def_init Name(): VICommandHandler()
#define VICommand_Name(Name) CommandName = Name; VICommandHost::getInstance()->addCommandHandler(this);}\
	bool handleCommand() override

class VIPublicAPI VICommandHost :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	friend class VICoreFramework;
	VI_Singleton(VICommandHost);
	_Private QMap<QString, VICommandHandler*> CommandHandlers;
	VI_PrivateProperty(QString, CommandOutput);
	_Protected def_init VICommandHost(QObject* parent = VI_NULLPTR);
	_Public bool addCommandHandler(VICommandHandler* handler);
	_Public void removeCommandHandler(VICommandHandler* handler);
	_Public bool handleCommand(const QString& command);
	_Public static QStringList blankSplitter(const QString& str);
	_Public static QStringList scientificSplitter(const QString& str, const QChar& ch);
};

class VIPublicAPI CommandHandlerTestClass :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init CommandHandlerTestClass(QObject* parent = VI_NULLPTR) :VIObject(parent) {};
	_Public VICommand_Handler(TestHandler) {
		VICommand_Name("TH") {
			qDebug() << "TestCommand";
			return true;
		}
	};
};