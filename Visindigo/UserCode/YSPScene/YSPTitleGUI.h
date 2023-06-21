#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "../../Visindigo/VIWidgets/VIWidgets.h"
#include "../YSPCore/YSPImageFilter.h"

class YSPTitleGUI :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Public VILabel* Title;
	_Public VILabel* SubTitle;
	_Public VILabel* Background;
	_Public VILabel* Logo;
	_Public VILabel* Splash;
	_Public def_init YSPTitleGUI(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		this->setStyleSheet("YSPTitleGUI{background-color:#000000;}");
		Background = new VILabel(this);
		Background->setAlignment(Qt::AlignCenter);
		Logo = new VILabel(this);
		Logo->setAlignment(Qt::AlignCenter);
		Title = new VILabel(this);
		Title->setAlignment(Qt::AlignCenter);
		Title->StyleSheetManager->addStyleSheet("Default", "VILabel{font-size:AUTO_50_PR;}");
		SubTitle = new VILabel(this);
		SubTitle->setAlignment(Qt::AlignCenter);
		Splash = new VILabel(this);
		Splash->setAlignment(Qt::AlignCenter);
	}
	_Public void resizeEvent(QResizeEvent* event) {
		Background->setGeometry(0, 0, this->width(), this->height());
		Title->setGeometry(QRect(0, this->height() * 0.40, this->width(), this->height() * 0.1666666));
		Title->StyleSheetManager->refreshStyleSheet();
		//Logo->setGeometry(
	}
	_Public void setBackgroundImage(QString path) {
		QImage img(path);
		YSPImageFilter::gaussianBlur(&img, 11);
		img.scaled(QSize(this->width(), this->height()), Qt::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
		Background->setPixmap(QPixmap::fromImage(img));
	}
};