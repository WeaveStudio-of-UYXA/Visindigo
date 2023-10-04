#include "VITR.h"
using namespace VIDocument;

def_init VITR::VITR() {
	Loaded = false;
}

bool VITR::load() {
	if (FilePath == "") { return false; }
	setObjectName(FilePath);
	QFile file(FilePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { return false; }
	QString LanguageName = FilePath.section("/", -1, -1).section(".", 0, -1);
	Translations.clear();
	QTextStream in(&file);
	in.setCodec("utf-8");
	QString line;
	while (!in.atEnd()) {
		line = in.readLine();
		if (line == "") { continue; }
		if (line.startsWith("#") || line.startsWith("//") || line.startsWith(" ")) { continue; }
		parseLine(line);
	}
	file.close();
	Loaded = true;
	return true;
}

void VITR::parseLine(const QString& line) {
	QString key = line.section(":", 0, 0);
	QString value = line.section(":", 1, -1);
	if (Translations.contains(key)) {
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Encountered redefined key: " + key + ", Redefining content ignored."));
	}
	else {
		Translations.insert(key, value);
	}
}

QString VITR::translate(const QString& key) {
	if (Translations.contains(key)) {
		return Translations[key];
	}
	else {
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "Encountered undefined key: " + key + ", Returning key as value."));
		return key;
	}
}