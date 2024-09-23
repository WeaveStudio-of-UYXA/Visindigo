#pragma once
#include "VIJsonConfig.h"

class VIJsonDocumentPrivate;
class VIMiCoreAPI VIJsonDocument
{
	friend class VIJsonConfigPrivate;
	_Public def_init VIJsonDocument();
	_Public def_init VIJsonDocument(const QString& configPath, const QString& defaultConfigPath);
	_Public def_copy VIJsonDocument(const VIJsonDocument& other) = delete;
	_Public def_move VIJsonDocument(VIJsonDocument&& other) = delete;
	_Public def_del ~VIJsonDocument();
	_Public QJsonParseError load(const QString& configPath = "", const QString& defaultConfigPath = "", uchar* whichError = nullptr, bool configAutoCreate = true);
	_Public void save();
	_Public QStringList keys(const QString& key = "");
	_Public QJsonValue getValue(const QString& key = "");
	_Public qint64 getInt(const QString& key = "");
	_Public QString getString(const QString& key = "");
	_Public bool getBool(const QString& key = "");
	_Public double getDouble(const QString& key = "");
	_Public VIJsonConfig getObject(const QString& key = "");
	_Public QList<VIJsonConfig> getArray(const QString& key = "");
	_Public bool contains(const QString& key);
	_Public void setValue(const QString& key, const QJsonValue& value);
	_Public void setInt(const QString& key, qint64 value);
	_Public void setString(const QString& key, const QString& value);
	_Public void setBool(const QString& key, bool value);
	_Public void setDouble(const QString& key, double value);
	_Public void setObject(const QString& key, const VIJsonConfig& value);
	_Public void setArray(const QString& key, const QList<VIJsonConfig>& value);
	_Public bool isEmpty(const QString& key = "");
	_Public bool isNull(const QString& key = "");
	_Public bool isObject(const QString& key = "");
	_Public bool isArray(const QString& key = "");
	_Public bool isString(const QString& key = "");
	_Public bool isBool(const QString& key = "");
	_Public bool isInt(const QString& key = "");
	_Public bool isDouble(const QString& key = "");
	_Private VIJsonDocumentPrivate* d;
};