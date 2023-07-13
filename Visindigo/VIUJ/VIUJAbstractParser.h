#pragma once
#include "../VICore/VICore.h"
#include "../VIWidgets/VIWidget.h"

typedef QMap<QString, QVariant> VIJsonValue;
class VIUJParserHost;

/*
VIUJAbstractParser
This class ONLY have ONE instance for each type of widget.
so, if you must save some data, you must use stack.
I know it's very foolish, but currently have no better way.
*/
class VIUJAbstractParser
{
	friend class VIUJParserHost;
	VI_ProtectedProperty(QString, TypeName);
	VI_ProtectedProperty(VIUJParserHost*, Host);
	_Private QStack<QWidget*> CurrentWidgetStack;
	_Public virtual QWidget* onJson(const QJsonObject& json) PureVirtual;
	_Public virtual void onNewChild(QWidget* child) PureVirtual;
	_Protected virtual QWidget* preOnJson(const QJsonObject& json) final;
	_Public QWidget* getCurrentWidget(){ return CurrentWidgetStack.top(); }
	_Public def_init VIUJAbstractParser(VIUJParserHost* host) {
		Host = host;
	}
};
class VIUJWidgetBinder;
typedef QMap<QString, VIUJAbstractParser*> VIUIJsonMap;
typedef QMap<QString, VIUJWidgetBinder*> VIUJWidgetBinderMap;
class VIUJParserHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIUJParserHost(VISuper* parent = VI_NULLPTR):VIObject(parent){}
	VI_PrivateProperty(VIUJAbstractParser*, RootUIJson);
	VI_PrivateProperty(VIUIJsonMap, UIJsonMap);
	VI_PrivateProperty(VIUJWidgetBinderMap, UJWidgetBinderMap);
	_Public void addUIJsonParser(VIUJAbstractParser* uiJson);
	_Public VIUJAbstractParser* getUIJsonParser(const QString& typeName);
	_Public void addUJWidgetBinder(VIUJWidgetBinder* ujWidgetBinder);
	_Public VIUJWidgetBinder* getUJWidgetBinder(const QString& instanceName);
	_Public QWidget* parse(const QString& fileName);
	_Public QWidget* parse(const QJsonObject& json);
	_Public static QWidget* findInstance(QWidget* root, const QString& instanceName);
};