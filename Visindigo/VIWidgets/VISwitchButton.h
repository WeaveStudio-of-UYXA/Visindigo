#pragma once
#include "VIWidget.h"
#include "VIWidgetsTransQt.h"
#include "private/VISwitchButton_p.h"

class VIPublicAPI VISwitchButton :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VILabel* DotLabel;
	_Private private_VISwitchButtonDotAnimationBehavior* DotAnimationBehavior;
	_Private bool Pressed;
	_Public def_init VISwitchButton(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		DotLabel = new VILabel(this);
		DotAnimationBehavior = new private_VISwitchButtonDotAnimationBehavior(this);
		DotAnimationBehavior->setTargetDot(DotLabel);
		DotAnimationBehavior->setTargetSwitchButton(this);
		Pressed = false;
		DotLabel->setVIDStyleSheet("default", 
			"VILabel{background-color:ACLR_"+VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Foreground) +
			"_CLR;border-radius:APR_50_PR;}"
		);
		qDebug()<<VIPaletteGroup::getInstance()->getColor(VIPalette::DefaultColorName::Foreground);
		DotLabel->applyVIDSS("default");
		this->setStyleSheet("VISwitchButton{background-color:rgb(255,255,255);border-radius:50px;border:3px solid blue;}");
	};
	_Public void resizeEvent(QResizeEvent* event) {
		DotLabel->resize(this->width() * 0.4, this->height() * 0.8);
		DotLabel->move(DotLabel->x(), this->height() * 0.1);
		DotLabel->refreshVIDStyleSheet();
		//refreshVIDStyleSheet();
	}
	_Public void enterEvent(QEvent* event) {
		DotAnimationBehavior->setDuration(300);
		DotAnimationBehavior->setCurrentAnimation(private_VISwitchButtonDotAnimationBehavior::CurrentAnimationType::Hover);
		DotAnimationBehavior->active();
	};
	_Public void leaveEvent(QEvent* event) {
		if (!Pressed) {
			DotAnimationBehavior->setDuration(300);
			DotAnimationBehavior->setCurrentAnimation(private_VISwitchButtonDotAnimationBehavior::CurrentAnimationType::Leave);
			DotAnimationBehavior->active();
		}
		Pressed = false;
	};
	_Public void mousePressEvent(QMouseEvent* event) {
		DotAnimationBehavior->setDuration(300);
		DotAnimationBehavior->setCurrentAnimation(private_VISwitchButtonDotAnimationBehavior::CurrentAnimationType::Press);
		DotAnimationBehavior->active();
		Pressed = true;
	};
};