﻿#pragma once
#include "../VIObject.h"
#include "../VIConsole.h"
#include "../VITranslationHost.h"
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
		_Public void loadDefaultFromStr(const QString& str);
		_Public void loadDefault(const QString& path);
		_Public bool loadSettings(const QString& path, bool autoCreate = false);
		_Public bool loadSettings(const QJsonObject& obj, const QString& path = "");
		_Public bool saveSettings(QString path = "");
		_Public const QVariant getValueOf(const QString& objName);
		_Public const QVariant operator[](const QString& objName);
		_Public const QStringList getKeysOf(const QString& objName);
		_Private const QStringList getKeysOf(bool* successflag, const QString& objName);
		_Private const QStringList getKeysOfDefault(bool* successflag, const QString& objName);
		_Private QVariant getValueOf(bool* successflag, const QString& objName);
		_Private QVariant getValueOfDefault(bool* successflag, const QString& objName);
		_Public void setValueOf(const QString& objName, const QVariant& value, bool allowAppend = true);
		_Private QJsonValue setValueOf(QStringList* nameList, QStringList::iterator* it, QJsonValue val, const QVariant& var);
	};
}
