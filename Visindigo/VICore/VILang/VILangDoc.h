#pragma once
#include "../VIObject.h"
#include "../VIConsole.h"

class VIPublicAPI VILanguageDoc :public VIObject
{
	_Public typedef QHash<QString, QString> TranslationsTable;
	Q_OBJECT;
	VI_OBJECT;
	_Private TranslationsTable Translations;
	_Private QString FilePath;
	_Private QString LanguageName;
	_Private bool Loaded = false;
	_Public def_init VILanguageDoc(QString filePath = "", VISuper* parent = VI_NULLPTR) :VIObject(parent) {
		FilePath = filePath;
	}
	_Public bool load() {
		return loadFrom(FilePath);
	}
	_Public bool loadFrom(QString path, bool append = false, bool _override = false) {
		if (path == "") { return false; }
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { return false; }
		FilePath = path;
		LanguageName = path.section("/", -1, -1).section(".", 0, -1);
		if (!append) { Translations.clear(); }
		QTextStream in(&file);
		in.setCodec("utf-8");
		QString line;
		while (!in.atEnd()) {
			line = in.readLine();
			if (line == "") { continue; }
			if (line.startsWith("#") || line.startsWith("//") || line.startsWith(" ")) { continue; }
			parseLine(line, _override);
		}
		file.close();
		Loaded = true;
		return true;
	}
	_Private void parseLine(QString line, bool _override) {
		QString key = line.section(":", 0, 0);
		QString value = line.section(":", 1, -1);
		if (Translations.contains(key)) {
			if (_override) {
				Translations[key] = value;
			}
			else {
				VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Encountered redefined key: " + key + ", Redefining content ignored."));
			}
		}
		else {
			Translations.insert(key, value);
		}
	}
	_Public QString translate(QString key) {
		if (Translations.contains(key)) {
			return Translations[key];
		}
		else {
			return key;
		}
	}
	_Public QString getLanguageName() { return LanguageName; }
	_Public bool isLoaded() { return Loaded; }
};

class VIPublicAPI VIMappingTranslator :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public typedef QHash<QString, QString> TranslationsHash;
	_Private TranslationsHash Translations;
	_Private QString FilePath;
	_Private QString LanguageName;
	_Private bool Loaded = false;
	_Public def_init VIMappingTranslator(QString filePath):VIObject() {
		FilePath = filePath;
	}
	_Public bool load() {
		return loadFrom(FilePath);
	}
	_Public bool loadFrom(QString path, bool append = false, bool _override = false) {
		if (path == "") { return false; }
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { return false; }
		FilePath = path;
		LanguageName = path.section("/", -1, -1).section(".", 0, -1);
		if (!append) { Translations.clear(); }
		QTextStream in(&file);
		in.setCodec("utf-8");
		QString line;
		while (!in.atEnd()) {
			line = in.readLine();
			if (line == "") { continue; }
			if (line.startsWith("#") || line.startsWith("//") || line.startsWith(" ")) { continue; }
			parseLine(line, _override);
		}
		file.close();
		Loaded = true;
		return true;
	}
	_Private void parseLine(QString line, bool _override) {
		QString key = line.section(":", 0, 0);
		QString value = line.section(":", 1, -1);
		if (Translations.contains(key)) {
			if (_override) {
				Translations[key] = value;
			}
			else {
				VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Encountered redefined key: " + key + ", Redefining content ignored."));
			}
		}
		else {
			Translations.insert(key, value);
		}
	}
	_Public QString translate(QString key) {
		if (Translations.contains(key)) {
			return Translations[key];
		}
		else {
			return key;
		}
	}
	_Public QString getLanguageName() { return LanguageName; }
	_Public bool isLoaded() { return Loaded; }
};