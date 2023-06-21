#pragma execution_character_set("utf-8")
#pragma once
#include "../../Visindigo/VICore/VICore.h"

class YSPPackageInfo :public VIPackageInfo
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init YSPPackageInfo(VIPackage* parent):VIPackageInfo(parent){
		setPackageName("YSP");
		setPackageVersionMajor(0);
		setPackageVersionMinor(10);
		setPackageVersionPatch(0);
		this->setAuthor(QStringList({ "Tsing Yayin", "Ayano Aishi", "Gradus" }));
		this->setDescription("专业咕咕");
		this->setLicense("GPL3.0");
		this->setURL("");
		this->setOrganization("Weave Studio & Studio Indigo");
		this->setOrganizationDomain("http://");
	}
};