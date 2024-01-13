/*
* 此文件含有您的项目的包元定义，您可以在此进行包的基础设置
*/
#pragma once
#include "../VICore/VICore.h"

namespace VIARCP {
	class VIPublicAPI PackageMeta :public VIPackageMeta
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public def_init PackageMeta() :VIPackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("VIARCP");
			this->setUniqueName(Unique_Visindigo_ARCP);
			this->PackageVersion = VIVersion(VI_VERSION_MAJOR, VI_VERSION_MINOR, VI_VERSION_PATCH);
			this->setAuthor({ "Tsing Yayin" });
			this->setDescription("Application Remote Call Protocol, suitable for program transmission of short messages in secure links");
			this->setLicense("LGPLv2.1");
			this->setURL("");
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
		}
	};
}