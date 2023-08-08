#pragma once
#include "../VIObject.h"
#include "../VIConsole.h"

namespace VIDocument {
	class VIPublicAPI VIJSON :public VIObject {
		Q_OBJECT;
		VI_OBJECT;
		_Private QJsonDocument Settings;
		_Private QString SettingsPath;
		_Private QString DefaultSettingsPath;
		_Private QJsonObject DefaultSettings;
		VI_Flag(SaveOnSet);
		_Public def_init VIJSON(QObject* parent = VI_NULLPTR);
		_Public void loadDefault(const QString& path);
		_Public bool loadSettings(const QString& path, bool autoCreate = false);
		_Public bool saveSettings(QString path = "");
		_Public const QVariant getValueOf(const QString& objName);
		_Private QVariant getValueOf(bool* successflag, const QString& objName);
		_Private QVariant getValueOfDefault(bool* successflag, const QString& objName);
		_Public void setValueOf(const QString& objName, const QVariant& value, bool allowAppend = true);
		_Private QJsonValue setValueOf(QStringList* nameList, QStringList::iterator* it, QJsonValue val, const QVariant& var);
	};
}

