/*
* 此文件初始化包的元数据和包的实例中的静态单例字段。
*/

#include "../$safeprojectname$Package.h"

VI_Singleton_StaticInit($safeprojectname$::PackageMeta);
VI_Singleton_StaticInit($safeprojectname$::Package);

def_init $safeprojectname$::PackageMeta::PackageMeta() :VIPackageMeta() {
    VI_Singleton_Init;
    this->setPackageName("$safeprojectname$");
    this->initFromMetaJson();
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