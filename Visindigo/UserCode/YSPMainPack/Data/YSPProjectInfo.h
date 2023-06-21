#pragma once
#include "../../../Visindigo/VICore/VICore.h"

class YSPProjectInfo :public VISettings
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init YSPProjectInfo(QString projectFolder, VISuper* parent = VI_NULLPTR) :VISettings(parent)
	{
		QFile defaultSettingsFile;
		defaultSettingsFile.setFileName(":/Visindigo/Resource/JSON/defaultProjectSettings.json");
		defaultSettingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream in(&defaultSettingsFile);
		in.setCodec("UTF-8");
		QString defaultSettings = in.readAll();
		this->setDefaultSettings(defaultSettings);
		this->loadSettings(projectFolder + "/projectSettings.json");
	}
	_Public QString getProjectVersion() {
		return this->getValueOf("projectVersion").toString();
	}
	_Public QString getProjectName() {
		return this->getValueOf("projectNickName").toString();
	}
	_Public QString getSPOLVersion() {
		return this->getValueOf("spolVersion").toString();
	}
	_Public QString getCodeEntry() {
		return this->getValueOf("codeEntry").toString();
	}
	_Public QStringList getJsFileIgnore() {
		return this->getValueOf("jsFileIgnore").toStringList();
	}
};