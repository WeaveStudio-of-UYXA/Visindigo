#pragma once
#include "VIObject.h"
#include "VIConsole.h"
class VIPublicAPI VISettings :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QJsonDocument Settings;
	_Private QString SettingsPath;
	_Private QJsonObject DefaultSettings;
	_Public def_init VISettings(QObject* parent = VI_NULLPTR);
	_Public void setDefaultSettings(const QJsonObject& settings);
	_Public void setDefaultSettings(const QString& settings);
	_Public bool loadSettings(const QString& path);
	_Public const QVariant getValueOf(const QString& objName);
};