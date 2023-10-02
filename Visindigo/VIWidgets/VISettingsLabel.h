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
	_Private QWidget* SettingsWidget = VI_NULL;
	_Public VIDocument::VIJSON* BindSettings = VI_NULL;
	_Public QString BindSettingsKey;
	_Protected QVariant CurrentValue;
	_Public def_init VISettingsLabel(QWidget* parent = VI_NULL, Visindigo::EmphasisSide layoutPolicy = Visindigo::DefaultEmphasis) : VIWidget(parent) {
		LayoutPolicy = layoutPolicy;
		if (LayoutPolicy == Visindigo::DefaultEmphasis) { LayoutPolicy = Visindigo::Left; }
		TitleLabel = new VIMultiLabel(this, LayoutPolicy);
		CurrentLayout = new QGridLayout(this);
		this->setLayout(CurrentLayout);
		switch (LayoutPolicy) {
		case Visindigo::Left:
			CurrentLayout->addWidget(TitleLabel, 0, 0, 1, 1);
			CurrentLayout->setColumnStretch(0, 3);
			CurrentLayout->setColumnStretch(1, 1);
			break;
		case Visindigo::Right:
			CurrentLayout->addWidget(TitleLabel, 0, 1, 1, 1);
			CurrentLayout->setColumnStretch(0, 1);
			CurrentLayout->setColumnStretch(1, 3);
			break;
		case Visindigo::Top:
			CurrentLayout->addWidget(TitleLabel, 0, 0, 1, 1);
			CurrentLayout->setRowStretch(0, 2);
			CurrentLayout->setRowStretch(1, 1);
			break;
		case Visindigo::Bottom:
			CurrentLayout->addWidget(TitleLabel, 1, 0, 1, 1);
			CurrentLayout->setRowStretch(0, 1);
			CurrentLayout->setRowStretch(1, 2);
			break;
		}
	}
	_Public void setSettingsWidget(QWidget* tar) {
		if (SettingsWidget != VI_NULL) {
			CurrentLayout->removeWidget(SettingsWidget);
			SettingsWidget->deleteLater();
		}
		SettingsWidget = tar;
		switch (LayoutPolicy) {
		case Visindigo::Left:
			CurrentLayout->addWidget(SettingsWidget, 0, 1, 1, 1);
			break;
		case Visindigo::Right:
			CurrentLayout->addWidget(SettingsWidget, 0, 0, 1, 1);
			break;
		case Visindigo::Top:
			CurrentLayout->addWidget(SettingsWidget, 1, 0, 1, 1);
			break;
		case Visindigo::Bottom:
			CurrentLayout->addWidget(SettingsWidget, 0, 0, 1, 1);
			break;
		}
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
	_Public void setBindSettings(VIDocument::VIJSON* settings, QString key) {
		BindSettings = settings;
		BindSettingsKey = key;
		CurrentValue = settings->getValueOf(key);
		onBindSettingsChanged();
	}
	_Public virtual void onBindSettingsChanged() PureVirtual;
	_Public void changeValue(const QVariant& value) {
		CurrentValue = value;
		if (BindSettings != VI_NULL) {
			BindSettings->setValueOf(BindSettingsKey, value);
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
		BoolButton = new VISwitchButton(this);
		connect(BoolButton, &VISwitchButton::clicked, this, &VISettingsLabel_Bool::onBoolButtonClicked);
	}
	_Public virtual void onBindSettingsChanged() override {
		BoolButton->setButtonState(CurrentValue.toBool());
	}
	_Public virtual void onBoolButtonClicked(bool state) {
		changeValue(state);
	}
};