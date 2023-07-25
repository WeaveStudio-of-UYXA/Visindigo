#include "../VIPackage.h"

VI_Singleton_Init(VIPackageInfo);

def_init VIPackageInfo::VIPackageInfo() {
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
	_instance = this;
}
QString VIPackageInfo::TR(const QString& key){
	return TranslationPackageHost->getTranslation(key);
}
void VIPackageInfo::addTranslationFileName(Visindigo::Language langType, const QString& key, bool inRC) {
	TranslationPackageHost->addTranslationFileName(langType, key, inRC);
}
void VIPackageInfo::setDefaultLanguage(Visindigo::Language langType) {
	TranslationPackageHost->setDefaultLanguage(langType);
}
void VIPackageInfo::initTranslation() {
	TranslationPackageHost->onInit();
}
void VIPackageInfo::addTranslatableObject(VITranslatableObject* obj) {
	TranslationPackageHost->addTranslatableObject(obj);
}