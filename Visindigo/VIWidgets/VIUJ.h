#pragma once
#include "../VICore/VICore.h"
#include "VIWidget.h"

typedef QMap<QString, QVariant> VIJsonValue;
class VIUIJsonParserHost;

/*
VIAbstractUJParser
This class ONLY have ONE instance for each type of widget.
so, if you must save some data, you must use stack.
I know it's very foolish, but currently have no better way.
*/
class VIAbstractUJParser
{
	friend class VIUIJsonParserHost;
	VI_ProtectedProperty(QString, TypeName);
	VI_ProtectedProperty(VIUIJsonParserHost*, Host);
	_Private QStack<QWidget*> CurrentWidgetStack;
	_Public virtual QWidget* onJson(const QJsonObject& json) PureVirtual;
	_Public virtual void onNewChild(QWidget* child) PureVirtual;
	_Protected virtual QWidget* preOnJson(const QJsonObject& json) final;
	_Public QWidget* getCurrentWidget(){ return CurrentWidgetStack.top(); }
	_Public def_init VIAbstractUJParser(VIUIJsonParserHost* host) {
		Host = host;
	}
};
class VIUJWidgetBinder;
typedef QMap<QString, VIAbstractUJParser*> VIUIJsonMap;
typedef QMap<QString, VIUJWidgetBinder*> VIUJWidgetBinderMap;
class VIUIJsonParserHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIUIJsonParserHost(VISuper* parent = VI_NULLPTR):VIObject(parent){}
	VI_PrivateProperty(VIAbstractUJParser*, RootUIJson);
	VI_PrivateProperty(VIUIJsonMap, UIJsonMap);
	VI_PrivateProperty(VIUJWidgetBinderMap, UJWidgetBinderMap);
	_Public void addUIJsonParser(VIAbstractUJParser* uiJson);
	_Public VIAbstractUJParser* getUIJsonParser(const QString& typeName);
	_Public void addUJWidgetBinder(VIUJWidgetBinder* ujWidgetBinder);
	_Public VIUJWidgetBinder* getUJWidgetBinder(const QString& instanceName);
	_Public QWidget* parse(const QString& fileName);
	_Public QWidget* parse(const QJsonObject& json);
	_Public static QWidget* findInstance(QWidget* root, const QString& instanceName);
};