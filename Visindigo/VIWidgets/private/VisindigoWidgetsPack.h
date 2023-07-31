#pragma once
#include "../../VICore/VICore.h"

namespace VisindigoWidgets {
	class VIPublicAPI PackageMeta :public VIPackageMeta
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		_Public def_init PackageMeta() {
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
			PackageMeta::setInstance(this);
		}
	};

	class VIPublicAPI Package :public VIPackage
	{
		Q_OBJECT;
		VI_OBJECT;
		_Public def_init Package() {
			setPackageMeta(new VisindigoWidgets::PackageMeta);
		}
	};
}