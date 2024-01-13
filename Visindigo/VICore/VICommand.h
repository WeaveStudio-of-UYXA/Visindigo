#pragma once
#include "VIObject.h"
#include "VIConsole.h"

using QStringMap = QMap<QString, QString> ;
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

class VIPublicAPI VIStdIOCommandHandler :public QThread, VIBaseObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VICommandHost;
	_Protected QMutex Mutex;
	_Protected bool Running = true;
	_Protected def_init VIStdIOCommandHandler(QObject* parent = VI_NULLPTR);
	_Signal void commandReceived(const QString& command);
	_Private virtual void run() override;
};

class VIPublicAPI VICommandHost :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	friend class VICoreFramework;
	VI_Singleton(VICommandHost);
	_Private QMap<QString, VICommandHandler*> CommandHandlers;
	_Private VIStdIOCommandHandler* StdIOListener = VI_NULLPTR;
	_Private bool ListenStdIO = false;
	VI_PrivateProperty(QString, CommandOutput);
	_Protected def_init VICommandHost(bool listenStdIO = true, QObject* parent = VI_NULLPTR);
	_Public bool addCommandHandler(VICommandHandler* handler);
	_Public void removeCommandHandler(VICommandHandler* handler);
	_Public bool handleCommand(const QString& command);
	_Public void enableStdIOListener();
	_Public void disableStdIOListener();
	_Public static QStringList blankSplitter(const QString& str);
	_Public static QStringList scientificSplitter(const QString& str, const QChar& ch); //just for compatibility
	_Public static QStringList scientificSplitter(const QString& str, const QString& ch);
	_Public static quint32 getIndentLevel(const QString& str, quint8 levelSize = 4);
	_Public static quint32 getIndentCount(const QString& str);
	_Public static void removeIndent(QString* str);
	_Public static void stringIndentStandardization(QString* str, quint8 levelSize = 4);
};