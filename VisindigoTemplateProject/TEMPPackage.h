/*
* 此文件含有您的项目的包元和包类的定义，您可以将包类的构造函数当做您的项目的入口函数。
*/
#pragma once
#include <VICore>
#include "CompileMacro.h"

namespace $safeprojectname$ {
	class $safeprojectname$PublicAPI PackageMeta :public VIPackageMeta
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public def_init PackageMeta() :VIPackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("$safeprojectname$");
			this->setPackageVersionMajor(0);
			this->setPackageVersionMinor(1);
			this->setPackageVersionPatch(0);
			this->setAuthor({ "$safeprojectname$ `s author"});
			this->setDescription("$safeprojectname$ do not have description yet!");
			this->setLicense("GPLv3.0");
			this->setURL("https://www.github.com/!!!YOUR_NAME!!!/$safeprojectname$");
			this->setOrganization("Weave Studio of UYXA");
			this->setOrganizationDomain("https://www.github.com/!!!YOUR_NAME!!!");
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
		}
	};

	class $safeprojectname$PublicAPI Package :public VIPackage, VITranslatableObject
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackage);
		VI_Singleton(Package);
		_Private QString t;
		_Public def_init Package() {
			VI_Singleton_Init;
			setPackageMeta(new $safeprojectname$::PackageMeta);
			getPackageMeta()->addTranslatableObject(this);
			getPackageMeta()->initTranslation();
		}
		_Public virtual void onTranslating() override {

		}

	};
}