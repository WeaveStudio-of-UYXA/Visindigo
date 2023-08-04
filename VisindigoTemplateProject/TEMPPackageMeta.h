/*
* 此文件含有您的项目的包元定义，您可以在此进行包的基础设置
*/
#pragma once
#include <VICore>
#include "private/$safeprojectname$CompileMacro.h"

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
	};
}