#pragma once
#include "../../VICore/VICore.h"

namespace VisindigoWidgets {
	class VIPublicAPI PackageMeta :public VIPackageMeta, VITranslatableObject
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public def_init PackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("VisindigoWidgets");
			this->setPackageVersionMajor(VI_VERSION_MAJOR);
			this->setPackageVersionMinor(VI_VERSION_MINOR);
			this->setPackageVersionPatch(VI_VERSION_PATCH);
			this->setAuthor({ "Tsing Yayin" });
			this->setDescription("The Visindigo Widgets provides components for building program UI.");
			this->setLicense("GPLv3.0");
			this->setURL("https://www.github.com/weavestudio-of-uyxa/visindigo");
			this->setOrganization("Weave Studio of UYXA");
			this->setOrganizationDomain("https://www.github.com/weavestudio-of-uyxa");
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
			this->addTranslatableObject(this);
		}
		_Public virtual void onTranslating() override {
			this->setDescription(getTranslation("Widgets_PackageMeta_Description"));
		}
	};

	class VIPublicAPI Package :public VIPackage
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackage);
		VI_Singleton(Package);
		_Public def_init Package() {
			VI_Singleton_Init;
			setPackageMeta(new VisindigoWidgets::PackageMeta);
			getPackageMeta()->initTranslation();
		}
	};
}