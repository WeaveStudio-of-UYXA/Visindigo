/*
* VIESEngine
* VIESEngine为Visindigo提供从ECMAScript调用的接口
* VIESEngine是单例的，用户不应当创建VIESEngine的新实例
* 如果用户需要另外驱动一个ECMAScript解释器，请使用VIECMAScript
*/
#pragma once
#include <QtQml>
#include "../../VICore/VIBehavior.h"

typedef QJSValue VIESPlugin;

class VIESEngine :public VIBasicBehavior
{
	Q_OBJECT;
	_Public QJSEngine* Engine;
	_Public QVector<VIESPlugin*> PluginList;
	_Public VIESPlugin* addPlugin(QString path) {};
	_Public def_init VIESEngine(QObject* parent = nullptr);
	_Public bool initPlugins() {};
	_Public bool execPlugins() {};
	_Public bool reciveEvent(...) {};
	_Public bool exitPlugins() {};
};