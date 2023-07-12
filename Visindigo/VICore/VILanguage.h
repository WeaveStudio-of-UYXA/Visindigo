#pragma once
#include "VIObject.h"
#include "VIDocument.h"
#include "VILang/VILangDoc.h"

class VILanguageHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void languageChanged();
	_Public enum class LangType {
		zh_SC, zh_TC, ja_JP, en_US,
		ko_KR, fr_FR, de_DE, ru_RU,
	};
	_Private VILanguageDoc* DefaultLanguage = VI_NULLPTR;
	_Private VILanguageDoc* CurrentLanguage = VI_NULLPTR;
	_Private VILanguageDoc* OverrideLanguage = VI_NULLPTR;
	VI_Property(QString, LanguagePath);
	VI_Property(LangType, DefaultLanguageType);
	VI_PrivateProperty(LangType, CurrentLanguageType);
	VI_PrivateFlag(Loaded);
	_Public def_init VILanguageHost(LangType currentType, LangType defaultType = LangType::zh_SC, QString langPath = "./Language", VISuper* parent = VI_NULLPTR);
	_Public static QString getLanguageName(LangType type);
	_Public bool loadLanguage();
	_Public bool appendOverrideLanguage(QString path);
	_Public void changeCurrentLanguage(LangType type);
	_Public static QString translate(VILanguageHost* instance, QString key) {
		if (instance == VI_NULLPTR) {
			return key;
		}
		if (!instance->Loaded) {
			return key;
		}
		QString tr = instance->OverrideLanguage->translate(key);
		if (tr != key) {
			return tr;
		}
		tr = instance->CurrentLanguage->translate(key);
		if (tr != key) {
			return tr;
		}
		tr = instance->DefaultLanguage->translate(key);
		if (tr != key) {
			return tr;
		}
		VIConsole::printLine(VIConsole::inWarningStyle(instance->getLogPrefix() + "Encountered undefined key: " + key + ", Returning key as value."));
		return tr;
	}
};

#define VITR(key) VILanguageHost::translate(VICoreFramework::getLanguageHostInstance(), key)