#include "../VILanguage.h"
def_init VILanguageHost::VILanguageHost(LangType currentType, LangType defaultType, QString langPath, VISuper* parent)
	:VIObject(parent) {
	setObjectName(getLanguageName(CurrentLanguageType));
	DefaultLanguageType = defaultType;
	CurrentLanguageType = currentType;
	LanguagePath = langPath;
	Loaded = false;
	OverrideLanguage = new VILanguageDoc("", this);
	consoleLog("DefaultLanguageType: " + getLanguageName(DefaultLanguageType));
	consoleLog("CurrentLanguageType: " + getLanguageName(CurrentLanguageType));
}
QString VILanguageHost::getLanguageName(LangType type) {
	switch (type)
	{
	case VILanguageHost::LangType::zh_SC:
		return "zh_SC";
	case VILanguageHost::LangType::zh_TC:
		return "zh_TC";
	case VILanguageHost::LangType::ja_JP:
		return "ja_JP";
	case VILanguageHost::LangType::en_US:
		return "en_US";
	case VILanguageHost::LangType::ko_KR:
		return "ko_KR";
	case VILanguageHost::LangType::fr_FR:
		return "fr_FR";
	case VILanguageHost::LangType::de_DE:
		return "de_DE";
	case VILanguageHost::LangType::ru_RU:
		return "ru_RU";
	default:
		return "zh_SC";
	}
}

bool VILanguageHost::loadLanguage() {
	if (CurrentLanguage != VI_NULLPTR) {
		delete CurrentLanguage;
	}
	if (DefaultLanguage != VI_NULLPTR) {
		delete DefaultLanguage;
	}
	if (DefaultLanguageType == CurrentLanguageType) {
		DefaultLanguage = new VILanguageDoc(LanguagePath + "/" + getLanguageName(DefaultLanguageType) + ".vil", this);
		DefaultLanguage->load();
		CurrentLanguage = DefaultLanguage;
	}
	else {
		DefaultLanguage = new VILanguageDoc(LanguagePath + "/" + getLanguageName(DefaultLanguageType) + ".vil", this);
		DefaultLanguage->load();
		CurrentLanguage = new VILanguageDoc(LanguagePath + "/" + getLanguageName(CurrentLanguageType) + ".vil", this);
		CurrentLanguage->load();
	}
	if (DefaultLanguage->isLoaded() && CurrentLanguage->isLoaded()) {
		Loaded = true;
	}
	else {
		Loaded = false;
	}
	return Loaded;
}
void VILanguageHost::changeCurrentLanguage(LangType type) {
	CurrentLanguageType = type;
	loadLanguage();
	emit languageChanged();
}
bool VILanguageHost::appendOverrideLanguage(QString Path) {
	return OverrideLanguage->loadFrom(Path, true, true);
}