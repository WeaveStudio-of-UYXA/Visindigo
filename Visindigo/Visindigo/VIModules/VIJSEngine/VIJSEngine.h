#pragma once
#include <QtCore>
#include <QtQml>
#include "../../../CommonEdit/CECore/CEMacro.h"
typedef QJSValue VIJSPlugin;

class VIJSEngine_Framework :public QObject
{
	Q_OBJECT;
	_Slot void refreshPlugins() {};
	_Slot void postEvent() {};
};
//此VIJSEngine专为事件驱动而设计
class VIJSEngine :public QObject
{
	Q_OBJECT;
	_Public QJSEngine* Engine;
	_Public QVector<VIJSPlugin*> PluginList;
	_Public VIJSPlugin* addPlugin(QString path) {};
	_Public def_init VIJSEngine(QObject* parent = nullptr);
	_Public bool initPlugins() {};
	_Public bool execPlugins() {};
	_Public bool reciveEvent(...) {};
	_Public bool exitPlugins() {};
};