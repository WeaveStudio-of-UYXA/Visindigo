#pragma once
#include "../../VICore/VICore.h"

namespace VisindigoWidgets {
	class PackageInfo :public VIPackageInfo
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageInfo);
		_Public def_init PackageInfo() {
			this->setPackageName("VisindigoWidgets");
			this->setPackageVersionMajor(VI_VERSION_MAJOR);
			this->setPackageVersionMinor(VI_VERSION_MINOR);
			this->setPackageVersionPatch(VI_VERSION_PATCH);
			this->setAuthor({ "Tsing Yayin", "Ayano Aishi", "v0v_tempest" });
			this->setDescription("The Visindigo Widgets provides components for building program UI.");
			this->setLicense("GPLv3.0");
			this->setURL("https://www.github.com/weavestudio-of-uyxa/visindigo");
			this->setOrganization("Weave Studio of UYXA");
			this->setOrganizationDomain("https://www.github.com/weavestudio-of-uyxa");
			PackageInfo::setInstance(this);
		}
	};

	class Package :public VIPackage
	{
		Q_OBJECT;
		VI_OBJECT;
		_Public def_init Package() {
			PackageInfo = new VisindigoWidgets::PackageInfo();
		}
	};
}