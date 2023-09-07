/*
* 此文件初始化包的元数据和包的实例中的静态单例字段。
*/

#include "../$safeprojectname$Package.h"

VI_Singleton_StaticInit($safeprojectname$::PackageMeta);
VI_Singleton_StaticInit($safeprojectname$::Package);

def_init $safeprojectname$::PackageMeta::PackageMeta() :VIPackageMeta() {
    VI_Singleton_Init;
    this->setPackageName("$safeprojectname$");
    this->setPackageVersionMajor($safeprojectname$_VERSION_MAJOR);
    this->setPackageVersionMinor($safeprojectname$_VERSION_MINOR);
    this->setPackageVersionPatch($safeprojectname$_VERSION_PATCH);
    this->setAuthor({ "$safeprojectname$ `s author"});
    this->setDescription("$safeprojectname$ do not have description yet!");
    this->setLicense("GPLv3.0");
    this->setURL("https://www.github.com/!!!YOUR_NAME!!!/$safeprojectname$");
    this->setOrganization("!!!YOUR_ORG_NAME!!!");
    this->setOrganizationDomain("https://www.github.com/!!!YOUR_ORG_NAME!!!");
    this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
    this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
    this->setDefaultLanguage(Visindigo::Language::zh_SC);
}

def_init $safeprojectname$::Package::Package() {
    VI_Singleton_Init;
    setPackageMeta(new $safeprojectname$::PackageMeta);
    getPackageMeta()->addTranslatableObject(this);
    getPackageMeta()->initTranslation();
}