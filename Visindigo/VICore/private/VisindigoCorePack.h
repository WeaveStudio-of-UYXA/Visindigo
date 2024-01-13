#pragma once
#include "../VIPackage.h"
#include "../VIVersion.h"

namespace VisindigoCore {
	class VIPublicAPI PackageMeta :public VIPackageMeta, VITranslatableObject
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public def_init PackageMeta() :VIPackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("VICore");
			this->initFromMetaJson();
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
			this->addTranslatableObject(this);
		}
		_Public virtual void onTranslating() override {
			this->setDescription(getTranslation("Core_PackageMeta_Description"));
		}
	};

	class VIPublicAPI Package :public VIPackage, VITranslatableObject
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackage);
		VI_Singleton(Package);
		_Private QString t;
		_Public def_init Package() {
			VI_Singleton_Init;
			setPackageMeta(new VisindigoCore::PackageMeta);
			getPackageMeta()->addTranslatableObject(this);
			getPackageMeta()->initTranslation();
		}
		_Public virtual void onTranslating() override {
		}
	};
}