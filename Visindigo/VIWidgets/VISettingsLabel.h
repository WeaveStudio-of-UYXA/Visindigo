#pragma once
#include "VIWidget.h"
#include "VIWidgetsTransQt.h"
#include "VIMultiLabel.h"
#include "VISwitchButton.h"

class VISettingsLabel :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public enum class SettingsType {
		Bool,
		StrLine,
		StrArea,
		Combo,
		MultiCombo,
		Ratio,
		Slider,
		SelectFile,
	};
	_Public VIMultiLabel* TitleLabel;
	VI_PrivateProperty(Visindigo::EmphasisSide, LayoutPolicy);
	VI_ProtectedProperty(SettingsType, Type);
	_Private QGridLayout* CurrentLayout;
	_Public QWidget* SettingsWidget = VI_NULL;
	_Public def_init VISettingsLabel(QWidget* parent = VI_NULL, Visindigo::EmphasisSide layoutPolicy = Visindigo::DefaultEmphasis) : VIWidget(parent) {
		LayoutPolicy = layoutPolicy;
		if (LayoutPolicy == Visindigo::DefaultEmphasis) { LayoutPolicy = Visindigo::Left; }
		TitleLabel = new VIMultiLabel(this, LayoutPolicy);
		CurrentLayout = new QGridLayout(this);
		this->setLayout(CurrentLayout);
	}
	_Public static const QString getSettingsTypeStr(SettingsType type) {
		switch (type) {
			VI_ENUMSTR(SettingsType, Bool);
			VI_ENUMSTR(SettingsType, StrLine);
			VI_ENUMSTR(SettingsType, StrArea);
			VI_ENUMSTR(SettingsType, Combo);
			VI_ENUMSTR(SettingsType, MultiCombo);
			VI_ENUMSTR(SettingsType, Ratio);
			VI_ENUMSTR(SettingsType, Slider);
			VI_ENUMSTR(SettingsType, SelectFile);
		}
	}
};

class VISettingsLabel_Bool :public VISettingsLabel
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VISwitchButton* BoolButton;
	_Public def_init VISettingsLabel_Bool(QWidget* parent = VI_NULL, Visindigo::EmphasisSide layoutPolicy = Visindigo::DefaultEmphasis) :
		VISettingsLabel(parent, layoutPolicy) {
		Type = SettingsType::Bool;

	}
};