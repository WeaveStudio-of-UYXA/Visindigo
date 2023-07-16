#include "../VISettings.h"

def_init VISettings::VISettings(VISuper* parent) :VIObject(parent) {
	this->setObjectName("VISettings");
	this->Settings = QJsonDocument();
}
void VISettings::setDefaultSettings(const QJsonObject& settings) {
	this->DefaultSettings = settings;
}
void VISettings::setDefaultSettings(const QString& settings) {
	this->DefaultSettings = QJsonDocument::fromJson(settings.toUtf8()).object();
}
bool VISettings::loadSettings(const QString& path) {
	QFile file(path);
	if (!file.exists()) {
		// Create file and write default settings
		QDir().mkpath(path.section('/', 0, -2));
		file.open(QIODevice::WriteOnly);
		file.write(QJsonDocument(this->DefaultSettings).toJson(QJsonDocument::Indented));
		file.close();
	}
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen()) {
		return false;
	}
	SettingsPath = path;
	QByteArray data = file.readAll();
	file.close();
	this->Settings = QJsonDocument::fromJson(data);
	return true;
}
const QVariant VISettings::getValueOf(const QString& objName) {
	QStringList objNameList = objName.split('.');
	QJsonObject obj = this->Settings.object();
	bool failToFind = false;
	for (auto i = objNameList.begin(); i != objNameList.end(); i++) {
		if (obj.contains(*i)) {
			if (i == objNameList.end() - 1) {
				return obj.value(*i).toVariant();
			}
			else {
				obj = obj.value(*i).toObject();
			}
		}
		else {
			failToFind = true;
		}
	}
	if (failToFind) {
		for (auto i = objNameList.begin(); i != objNameList.end(); i++) {
			if (this->DefaultSettings.contains(*i)) {
				if (i == objNameList.end() - 1) {
					VIConsole::printLine(VIConsole::inErrorStyle(getLogPrefix() + "Can't find settings: " + objName + ", use default value."));
					return this->DefaultSettings.value(*i).toVariant();
				}
				else {
					obj = this->DefaultSettings.value(*i).toObject();
				}
			}
			else {
				VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "No such settings:" + objName));
				return QVariant();
			}
		}
	}
	VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "No such settings:" + objName));
	return QVariant();
}