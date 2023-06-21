#pragma once
#include "../VICore/VICore.h"
#include "VIWidget.h"

class VIPackagePanel :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Private VIPackage* Package;
	VI_PrivateProperty(QLabel*, PackageNameLabel);
	_Public def_init VIPackagePanel(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		this->setWindowTitle("Visindigo Package Panel");
	}
};