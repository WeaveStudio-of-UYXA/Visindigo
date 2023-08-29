#include "../VITranslationHost.h"
#include "../VICoreFramework.h"
#include "../VIVersion.h"

VITranslationSubHost* VITranslatableObject::getTRHost() {
	return TRHost;
}
void VITranslatableObject::setTRHost(VITranslationSubHost* host) {
	TRHost = host;
}
QString VITranslatableObject::getTranslation(const QString& key) {
	if (TRHost == VI_NULL) {
		return key;
	}
	else {
		return TRHost->getTranslation(key);
	}
}

def_init VITranslationSubHost::VITranslationSubHost(VIPackageMeta* parent) :VIObject() {
	ParentPackage = parent;
	CurrentDoc = VI_NULL;
	DefaultDoc = VI_NULL;
	DefaultLanguage = Visindigo::Language::zh_TC;
}

void VITranslationSubHost::addTranslatableObject(VITranslatableObject* t) {
	if (!TargetList.contains(t)) {
		TargetList.push_back(t);
		t->setTRHost(this);
	}
}

void VITranslationSubHost::addTranslationFileName(Visindigo::Language lang, const QString& filename, bool inRC) {
	if (!LanguageFileNames.contains(lang)) {
		VITRFileInfo info;
		info.FileName = filename;
		info.inRC = inRC;
		LanguageFileNames.insert(lang, info);
	}
}

void VITranslationSubHost::onGlobalLanguageChange(Visindigo::Language langName) {
	loadVITRDocument(&CurrentDoc, langName);
	for (int i = 0; i < TargetList.size(); i++) {
		TargetList[i]->onTranslating();
	}
}

void VITranslationSubHost::onInit() {
	setObjectName(ParentPackage->PackageName);
	loadVITRDocument(&DefaultDoc, DefaultLanguage);
	onGlobalLanguageChange(VICoreFrame->getLanguageType());
}

QString VITranslationSubHost::getTranslation(const QString& key) {
	QString rtn;
	qDebug() << CurrentDoc;
	qDebug() << DefaultDoc;
	if (CurrentDoc != VI_NULL) {
		rtn = CurrentDoc->translate(key);
		if (rtn != key) { return rtn; }
		else {
			if (DefaultDoc != VI_NULL) {
				rtn = DefaultDoc->translate(key);
				if (rtn != key) { return rtn; }
				else {
					rtn = VICoreFrame->getTranslationHostInstance()->topTranslation(key);
					if (rtn != key) { return rtn; }
					else { return key; }
				}
			}
		}
	}
	return key;
}
bool VITranslationSubHost::loadVITRDocument(VIDocument::VITR** docPtr, Visindigo::Language langName) {
	if (!LanguageFileNames.contains(langName)) {
		VIConsole::printLine(VIConsole::inWarningStyle("The Package '" +
			ParentPackage->getPackageName() + "' dose not support the language."));
		return false;
	}
	QString fileName = LanguageFileNames[langName].FileName;
	QString filePath;
	if (!LanguageFileNames[langName].inRC) {
		filePath = ParentPackage->getPackageRootPath() + "/i18n/" + fileName;
	}
	else {
		filePath = ParentPackage->getPackageInternalPath() + "/i18n/" + fileName;
	}
	consoleLog("Loading file in: '" + filePath + "'");
	VIDocument::VITR* doc = new VIDocument::VITR();
	doc->setFilePath(filePath);
	bool result = doc->load();
	qDebug() << result;
	if (result) {
		if ((*docPtr) != VI_NULL) {
			(*docPtr)->deleteLater();
		}
		*docPtr = doc;
		return true;
	}
	else {
		doc->deleteLater();
		return false;
	}
}

/*
VITranslationHost
*/

def_init VITranslationHost::VITranslationHost(VISuper* parent) :VIObject(parent) {
	setObjectName(VIVersion::getVisindigoVersion());
	consoleLog("Host instance created");
}
void VITranslationHost::changeLanguage(Visindigo::Language lang) {
	for (auto i = VICoreFrame->AppInstance->PackageList.begin(); i != VICoreFrame->AppInstance->PackageList.end(); i++) {
		(*i)->getPackageMeta()->TranslationPackageHost->onGlobalLanguageChange(lang);
	}
}

QString VITranslationHost::topTranslation(const QString& key) {
	return ""; // Not implemented yet, maybe in the future
}