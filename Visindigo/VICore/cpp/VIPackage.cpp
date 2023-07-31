#include "../VIPackage.h"

VI_Singleton_Init(VIPackageMeta);

def_init VIPackageMeta::VIPackageMeta() {
	this->setPackageName("UnnamedVIPackage");
	this->setPackageVersionMajor(0);
	this->setPackageVersionMinor(0);
	this->setPackageVersionPatch(0);
	this->setAuthor(QStringList());
	this->setDescription("");
	this->setLicense("");
	this->setURL("");
	this->setOrganization("");
	this->setOrganizationDomain("");
	this->TranslationPackageHost = new VITranslationSubHost(this);
	this->PackageConfig = new VIDocument::VIJSON(this);
	_instance = this;
}
QString VIPackageMeta::TR(const QString& key){
	return TranslationPackageHost->getTranslation(key);
}
void VIPackageMeta::addTranslationFileName(Visindigo::Language langType, const QString& key, bool inRC) {
	TranslationPackageHost->addTranslationFileName(langType, key, inRC);
}
void VIPackageMeta::setDefaultLanguage(Visindigo::Language langType) {
	TranslationPackageHost->setDefaultLanguage(langType);
}
void VIPackageMeta::initTranslation() {
	TranslationPackageHost->onInit();
}
void VIPackageMeta::addTranslatableObject(VITranslatableObject* obj) {
	TranslationPackageHost->addTranslatableObject(obj);
}
void VIPackageMeta::setPackageName(const QString& name) {
	PackageName = name;
	setObjectName(name);
}
QString VIPackageMeta::getPackageName() {
	return PackageName;
}
QVariant VIPackageMeta::getConfig(const QString& key) {
	return PackageConfig->getValueOf(key);
}
void VIPackageMeta::setConfig(const QString& key, const QVariant& value) {
	PackageConfig->setValueOf(key, value);
}
void VIPackageMeta::initConfig() {
	PackageConfig->loadDefault(getPackageInternalPath()+"/config.json");
	PackageConfig->loadSettings(getPackageRootPath() + "/config.json");
	PackageConfig->setObjectName(PackageName);
}
def_del VIPackageMeta::~VIPackageMeta() {
	delete TranslationPackageHost;
	PackageConfig->saveSettings();
	delete PackageConfig;
}
/*
VIPackage
*/
def_init VIPackage::VIPackage() {
	PackageMeta = VI_NULL;
}
VIPackageMeta* VIPackage::getPackageMeta() {
	return PackageMeta;
}
void VIPackage::setPackageMeta(VIPackageMeta* info) {
	if (info != VI_NULL) {
		if (PackageMeta != VI_NULL) {
			return;
		}
		PackageMeta = info;
		setObjectName(info->getPackageName());
		VIConsole::printLine(VIConsole::inSuccessStyle(getLogPrefix()+"Package Meta loaded."));
	}
}
def_del VIPackage::~VIPackage() {
	if (PackageMeta != VI_NULL) {
		delete PackageMeta;
	}
}