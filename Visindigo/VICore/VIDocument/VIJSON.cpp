﻿#include "VIJSON.h"
#include "../VICommand.h"
#include "../private/VisindigoCorePack.h"
namespace VIDocument {
	def_init VIJSON::VIJSON(VISuper* parent) :VIObject(parent) {
		this->setObjectName("VIJSON");
		this->SaveOnSet = false;
		this->DefaultSettingsPath = "";
		this->SettingsPath = "";
	}
	void VIJSON::loadDefaultFromStr(const QString& str) {
		this->DefaultSettings = QJsonDocument::fromJson(str.toUtf8()).object();
	}
	void VIJSON::loadDefault(const QString& path) {
		QFile file(path);
		if (!file.exists()) {
			return;
		}
		file.open(QIODevice::ReadOnly);
		if (!file.isOpen()) {
			return;
		}
		DefaultSettingsPath = path;
		QTextStream data(&file);
		data.setCodec("UTF-8");
		this->DefaultSettings = QJsonDocument::fromJson(data.readAll().toUtf8()).object();
		file.close();
	}
	bool VIJSON::loadSettings(const QString& path, bool autoCreate) {
		QFile file(path);
		if (!file.exists()) {
			if (!autoCreate) { return false; }
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
		setObjectName(path);
		QTextStream data(&file);
#if QT_VERSION_MAJOR == 5
		data.setCodec("UTF-8");
#pragma throw_warning(10000, "有一个已缓解的Qt5和Qt6的迁移兼容问题")
#elif QT_VERSION_MAJOR == 6
		data.setEncoding(QStringConverter::Utf8);
#endif
		this->Settings = QJsonDocument::fromJson(data.readAll().toUtf8());
		file.close();
		return true;
	}
	bool VIJSON::loadSettings(const QJsonObject& obj, const QString& path) {
		this->Settings = QJsonDocument(obj);
		this->SettingsPath = path;
		return true;
	}
	bool VIJSON::saveSettings(QString path) {
		if (path == "") { path = SettingsPath; }
		if (path == "") { return false; }
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly)) {
			return false;
		}
		file.write(Settings.toJson(QJsonDocument::Indented));
		file.close();
		return true;
	}
	const QVariant VIJSON::getValueOf(const QString& objName) {
		bool flag = false;
		QVariant value = this->getValueOf(&flag, objName);
		if (flag) {
			return value;
		}
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Unable to find value for '" + objName + "', search for default document"));
		value = this->getValueOfDefault(&flag, objName);
		if (flag) {
			VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Found value for '" + objName + "' in default document, already written to the active document"));
			setValueOf(objName, value);
			return value;
		}
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Unable to find value for '" + objName + "' in default document"));
		return QVariant();
	}
	const QVariant VIJSON::operator[](const QString& objName) {
		return this->getValueOf(objName);
	}
	const QStringList VIJSON::getKeysOf(const QString& objName) {
		bool flag = false;
		QStringList keys = this->getKeysOf(&flag, objName);
		if (flag) {
			return keys;
		}
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Unable to find keys for '" + objName + "', search for default document"));
		keys = this->getKeysOfDefault(&flag, objName);
		if (flag) {
			VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Found keys for '" + objName + "' in default document, already written to the active document"));
			setValueOf(objName, keys);
			return keys;
		}
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Unable to find keys for '" + objName + "' in default document"));
		return QStringList();
	}
	const QStringList VIJSON::getKeysOf(bool* successflag, const QString& objName) {
		QStringList objNameList = VICommandHost::scientificSplitter(objName, '.');
		QJsonObject obj = this->Settings.object();
		QJsonArray arr;
		bool isArray = false;//下面这些鬼扯玩意就应该用递归
		for (auto i = objNameList.begin(); i != objNameList.end(); i++) {
			if (isArray) {
				if (i->toInt() > arr.size() || i->toInt() < 0) { break; }
				if (i == objNameList.end() - 1) {
					*successflag = true;
					QJsonValue la = arr.at(i->toInt());
					if (la.isArray()) {
						int size = la.toArray().size();
						QStringList result;
						for (int i = 0; i < size; i++) {
							result.append(QString::number(i));
						}
						return result;
					}
					else if (la.isObject()) {
						return la.toObject().keys();
					}
					else {
						return QStringList();
					}
				}
				else {
					if (arr.at(i->toInt()).isArray()) { arr = arr.at(i->toInt()).toArray(); }
					else {
						obj = arr.at(i->toInt()).toObject();
						isArray = false;
					}
				}
			}
			else {
				if (obj.contains(*i)) {
					if (i == objNameList.end() - 1) {
						*successflag = true;
						QJsonValue la = obj.value(*i);
						if (la.isArray()) {
							int size = la.toArray().size();
							QStringList result;
							for (int i = 0; i < size; i++) {
								result.append(QString::number(i));
							}
							return result;
						}
						else if (la.isObject()) {
							return la.toObject().keys();
						}
						else {
							return QStringList();
						}
					}
					else {
						if (obj.value(*i).isArray()) {
							arr = obj.value(*i).toArray();
							isArray = true;
						}
						else { obj = obj.value(*i).toObject(); }
					}
				}
				else { break; }
			}
		}
		*successflag = false;
		return QStringList();
	}
	const QStringList VIJSON::getKeysOfDefault(bool* successflag, const QString& objName) {
		QStringList objNameList = VICommandHost::scientificSplitter(objName, '.');
		QJsonObject obj = this->DefaultSettings; //没记错的话这玩意有隐式共享，问题不大
		QJsonArray arr;
		bool isArray = false;//下面这些鬼扯玩意就应该用递归
		for (auto i = objNameList.begin(); i != objNameList.end(); i++) {
			if (isArray) {
				if (i->toInt() > arr.size() || i->toInt() < 0) { break; }
				if (i == objNameList.end() - 1) {
					*successflag = true;
					QJsonValue la = arr.at(i->toInt());
					if (la.isArray()) {
						int size = la.toArray().size();
						QStringList result;
						for (int i = 0; i < size; i++) {
							result.append(QString::number(i));
						}
						return result;
					}
					else if (la.isObject()) {
						return la.toObject().keys();
					}
					else {
						return QStringList();
					}
				}
				else {
					if (arr.at(i->toInt()).isArray()) { arr = arr.at(i->toInt()).toArray(); }
					else {
						obj = arr.at(i->toInt()).toObject();
						isArray = false;
					}
				}
			}
			else {
				if (obj.contains(*i)) {
					if (i == objNameList.end() - 1) {
						*successflag = true;
						QJsonValue la = obj.value(*i);
						if (la.isArray()) {
							int size = la.toArray().size();
							QStringList result;
							for (int i = 0; i < size; i++) {
								result.append(QString::number(i));
							}
							return result;
						}
						else if (la.isObject()) {
							return la.toObject().keys();
						}
						else {
							return QStringList();
						}
					}
					else {
						if (obj.value(*i).isArray()) {
							arr = obj.value(*i).toArray();
							isArray = true;
						}
						else { obj = obj.value(*i).toObject(); }
					}
				}
				else { break; }
			}
		}
		*successflag = false;
		return QStringList();
	}
	QVariant VIJSON::getValueOf(bool* successflag, const QString& objName) {
		QStringList objNameList = VICommandHost::scientificSplitter(objName, '.');
		QJsonObject obj = this->Settings.object();
		QJsonArray arr;
		bool isArray = false;//下面这些鬼扯玩意就应该用递归
		for (auto i = objNameList.begin(); i != objNameList.end(); i++) {
			if (isArray) {
				if (i->toInt() > arr.size() || i->toInt() < 0) { break; }
				if (i == objNameList.end() - 1) {
					*successflag = true;
					return arr.at(i->toInt()).toVariant();
				}
				else {
					if (arr.at(i->toInt()).isArray()) { arr = arr.at(i->toInt()).toArray(); }
					else {
						obj = arr.at(i->toInt()).toObject();
						isArray = false;
					}
				}
			}
			else {
				if (obj.contains(*i)) {
					if (i == objNameList.end() - 1) {
						*successflag = true;
						return obj.value(*i).toVariant();
					}
					else {
						if (obj.value(*i).isArray()) {
							arr = obj.value(*i).toArray();
							isArray = true;
						}
						else { obj = obj.value(*i).toObject(); }
					}
				}
				else { break; }
			}
		}
		*successflag = false;
		return QVariant();
	}
	QVariant VIJSON::getValueOfDefault(bool* successflag, const QString& objName) {
		QStringList objNameList = VICommandHost::scientificSplitter(objName, '.');
		QJsonObject obj = this->DefaultSettings; //没记错的话这玩意有隐式共享，问题不大
		QJsonArray arr;
		bool isArray = false;//下面这些鬼扯玩意就应该用递归
		for (auto i = objNameList.begin(); i != objNameList.end(); i++) {
			if (isArray) {
				if (i->toInt() > arr.size() || i->toInt() < 0) { break; }
				if (i == objNameList.end() - 1) {
					*successflag = true;
					return arr.at(i->toInt()).toVariant();
				}
				else {
					if (arr.at(i->toInt()).isArray()) { arr = arr.at(i->toInt()).toArray(); }
					else {
						obj = arr.at(i->toInt()).toObject();
						isArray = false;
					}
				}
			}
			else {
				if (obj.contains(*i)) {
					if (i == objNameList.end() - 1) {
						*successflag = true;
						return obj.value(*i).toVariant();
					}
					else {
						if (obj.value(*i).isArray()) {
							arr = obj.value(*i).toArray();
							isArray = true;
						}
						else { obj = obj.value(*i).toObject(); }
					}
				}
				else { break; }
			}
		}
		*successflag = false;
		return QVariant();
	}
	void VIJSON::setValueOf(const QString& objName, const QVariant& value, bool allowAppend) {
		if (objName == "") { return; }
		bool haveValue = false;
		if (!allowAppend) {
			getValueOfDefault(&haveValue, objName);
			if (!haveValue) { return; }
		}
		QStringList objNameList = VICommandHost::scientificSplitter(objName, '.');
		QStringList::iterator it = objNameList.begin();
		QJsonValue val = setValueOf(&objNameList, &it, this->Settings.object(), value);
		this->Settings.setObject(val.toObject());
		consoleLog("Set value of '" + objName + "' to '" + value.toString() + "'");
		if (this->SaveOnSet) {
			this->saveSettings();
		}
	}
	QJsonValue VIJSON::setValueOf(QStringList* nameList, QStringList::iterator* it, QJsonValue val, const QVariant& var) {
		if (*it == nameList->end() - 1) {
			if (val.isArray()) {
				QJsonArray arr = val.toArray();
				if (arr.size() <= (*it)->toInt()) {
					arr.append(QJsonValue::fromVariant(var));
				}
				else {
					arr.replace((*it)->toInt(), QJsonValue::fromVariant(var));
				}
				return arr;
			}
			else {
				QJsonObject obj = val.toObject();
				obj.insert(*(*it), QJsonValue::fromVariant(var));
				return obj;
			}
		}
		else {
			QStringList::iterator it2 = *it + 1;
			if (val.isArray()) {
				QJsonArray arr = val.toArray();
				arr.replace((*it)->toInt(), setValueOf(nameList, &it2, arr.at((*it)->toInt()), var));
				return arr;
			}
			else {
				QJsonObject obj = val.toObject();
				obj.insert(*(*it), setValueOf(nameList, &it2, obj.value(*(*it)), var));
				return obj;
			}
		}
	}
}