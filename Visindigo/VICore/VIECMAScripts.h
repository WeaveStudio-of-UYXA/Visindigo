#pragma once
#include "private/VIECMABuiltInModules.h"
#include "VICommand.h"

typedef QMap<QString, QString> VIECMAModuleMap;
enum class VIECMABuiltInModule {
	System, Console
};

class VIECMAScripts;

class VIPublicAPI private_VIECMAScripts :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	friend class VIECMAScripts;
	_Signal void finished();
	_Signal void boot(QString fileName, QString entry = "main");
	VI_ProtectedProperty(QJSEngine*, engine);
	VI_ProtectedProperty(QList<VIECMABuiltInModule>, BuiltInModules);
	VI_ProtectedProperty(QList<VIObject*>, VIObjectModules);
	VI_ProtectedProperty(VIECMAModuleMap, Modules);
	VI_ProtectedProperty(QMutex*, ThreadMutex);
	VI_ProtectedProperty(QWaitCondition*, ThreadWaitCondition);
	VI_ProtectedFlag(InThread);
	VI_ProtectedFlag(DelLater);
	_Protected def_init private_VIECMAScripts();
	_Protected static void registerBuiltInModule(QJSEngine* engine, VIECMABuiltInModule module);
	_Protected void importVIObject(VIObject* obj);
	_Slot void sideLoad(const QString& fileName);
	_Slot void onBoot(const QString& fileName, const QString& entry = "main");
};

class VIPublicAPI VIECMAScripts :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	_Signal void finished();
	VI_Property(QThread*, Thread);
	VI_PrivateProperty(QWaitCondition*, ThreadWaitCondition);
	VI_PrivateProperty(QMutex*, ThreadMutex);
	VI_PrivateProperty(QList<VIECMABuiltInModule>, BuiltInModules);
	VI_PrivateProperty(VIECMAModuleMap, Modules);
	VI_PrivateProperty(private_VIECMAScripts*, VIECMAS);
	VI_PrivateProperty(QList<VIObject*>, VIObjectModules);
	VI_Flag(OnRunning);
	VI_Flag(SideLoaded);
	_Public def_init VIECMAScripts();
	_Public void boot(const QString& fileName, const QString& entry = "main");
	_Public void threadBoot(const QString& fileName, const QString& entry = "main");
	_Private void boot(QString fileName, bool inThread = false, QString entry = "main");
	_Public void importBuiltInModule(VIECMABuiltInModule module);
	_Public void importModule(const QString& name, const QString& path);
	_Public void importVIObject(VIObject* obj);
	_Public void sideLoad(QString fileName);
	_Public void unload();
	_Public QJSValue getGlobalObject(QString name);
	_Private void onExit();
	_Public def_del ~VIECMAScripts();
};
