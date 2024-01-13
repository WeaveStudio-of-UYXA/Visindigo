#pragma once
#include "../VICore/VICore.h"
#include "VIWidget.h"

class VIPublicAPI VIPackagePanel :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Private VIPackage* Package;
	_Private QLabel* Name;
	_Private QLabel* Version;
	_Private QLabel* Author;
	_Private QLabel* Description;
	_Private QLabel* License;
	_Private QLabel* URL;
	_Private QVBoxLayout* MainLayout;
	_Public def_init VIPackagePanel(VIPackage* targetPack, QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		Package = targetPack;
		Name = new QLabel(this);
		Version = new QLabel(this);
		Author = new QLabel(this);
		Description = new QLabel(this);
		License = new QLabel(this);
		URL = new QLabel(this);
		MainLayout = new QVBoxLayout(this);
		MainLayout->addWidget(Name);
		MainLayout->addWidget(Version);
		MainLayout->addWidget(Author);
		MainLayout->addWidget(Description);
		MainLayout->addWidget(License);
		MainLayout->addWidget(URL);
		License->hide();
		URL->hide();
		this->setLayout(MainLayout);
		VisindigoWidgets::PackageMeta::getInstance()->addTranslatableObject(this);
		onTranslating();
	}
	_Public virtual void enterEvent(QEvent* event) override {
		License->show();
		URL->show();
	}
	_Public virtual void leaveEvent(QEvent* event) override {
		License->hide();
		URL->hide();
	}
	_Public virtual void onTranslating()override {
		Name->setText(getTranslation("Widgets_PackagePanel_Name") + ": " + Package->getPackageMeta()->getPackageName());
		Version->setText(getTranslation("Widgets_PackagePanel_Version") + ": " + Package->getPackageMeta()->getPackageVersion().getVersionString());
		Author->setText(getTranslation("Widgets_PackagePanel_Author") + ": " + Package->getPackageMeta()->getAuthor().join(", "));
		Description->setText(getTranslation("Widgets_PackagePanel_Description") + ": " + Package->getPackageMeta()->getDescription());
		License->setText(getTranslation("Widgets_PackagePanel_License") + ": " + Package->getPackageMeta()->getLicense());
		URL->setText(getTranslation("Widgets_PackagePanel_Website") + ": " + Package->getPackageMeta()->getURL());
	}
};

class TestPanelClass :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public QGridLayout* CurrentLayout;
	_Public def_init TestPanelClass(QWidget* parent = VI_NULL) :VIWidget(parent) {
		CurrentLayout = new QGridLayout(this);
		this->setLayout(CurrentLayout);
		QList<VIPackageUniqueName> VIF = VICoreFrame->getPackageNames();
		for (auto i = VIF.begin(); i != VIF.end(); i++) {
			VIPackagePanel* Panel = new VIPackagePanel(VICoreFrame->getPackage(*i), this);
			CurrentLayout->addWidget(Panel);
		}
	}
};