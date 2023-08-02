#pragma once
#include "../VIPackage.h"
#include "../VIVersion.h"

namespace VisindigoCore {
	class VIPublicAPI PackageMeta :public VIPackageMeta
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public def_init PackageMeta():VIPackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("VisindigoCore");
			this->setPackageVersionMajor(VI_VERSION_MAJOR);
			this->setPackageVersionMinor(VI_VERSION_MINOR);
			this->setPackageVersionPatch(VI_VERSION_PATCH);
			this->setAuthor({ "Tsing Yayin", "Ayano Aishi", "v0v_tempest" });
			this->setDescription("The Visindigo Core provides basic and non UI type components for Visindigo. To use Visindigo, the Visindigo Core must be included in the project");
			this->setLicense("GPLv3.0");
			this->setURL("https://www.github.com/weavestudio-of-uyxa/visindigo");
			this->setOrganization("Weave Studio of UYXA");
			this->setOrganizationDomain("https://www.github.com/weavestudio-of-uyxa");
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
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
			qDebug() << getPackageMeta()->getPackageRootPath();
		}
		_Public virtual void onTranslating() override {
			t = getTranslation("Core_LanguageHost_LoadLanguage_Success");
			consoleLog("Translated!");
		}
		_Public void printT() {
			qDebug() << t;
		}
	};
}