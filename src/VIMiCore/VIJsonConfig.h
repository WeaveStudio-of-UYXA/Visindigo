#pragma once
#include "VIObject.h"
#include <QJsonValue>
#include <QJsonDocument>

class VIJsonConfigPrivate;
class VIMiCoreAPI VIJsonConfig 
{
	friend class VIJsonConfigPrivate;
	_Public def_init VIJsonConfig();
	_Public def_init VIJsonConfig(const QString& jsonStr);
	_Public def_init VIJsonConfig(const QJsonDocument& json);
	_Public def_copy VIJsonConfig(const VIJsonConfig& other) noexcept;
	_Public def_move VIJsonConfig(VIJsonConfig&& other) noexcept;
	_Public def_del ~VIJsonConfig();
	_Public def_copy VIJsonConfig& operator=(const VIJsonConfig& other) noexcept;
	_Public def_move VIJsonConfig& operator=(VIJsonConfig&& other) noexcept;
	_Public QStringList keys(const QString& key = "");
	_Public QJsonParseError parse(const QString& jsonStr);
	_Public QString toString(QJsonDocument::JsonFormat format = QJsonDocument::Indented);
	_Public QJsonValue getValue(const QString& key = "", bool* ok = nullptr);
	_Public qint64 getInt(const QString& key = "", bool* ok = nullptr);
	_Public QString getString(const QString& key = "", bool* ok = nullptr);
	_Public bool getBool(const QString& key = "", bool* ok = nullptr);
	_Public double getDouble(const QString& key = "", bool* ok = nullptr);
	_Public VIJsonConfig getObject(const QString& key = "", bool* ok = nullptr);
	_Public QList<VIJsonConfig> getArray(const QString& key = "", bool* ok = nullptr);
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
	_Private VIJsonConfigPrivate* d;
};