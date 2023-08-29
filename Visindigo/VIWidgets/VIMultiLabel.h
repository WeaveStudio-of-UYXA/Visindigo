#pragma once
#include "VIWidgetsTransQt.h"
#include "VIWidget.h"

class VIPublicAPI VIMultiLabel :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VILabel* IconLabel;
	_Public VILabel* TextLabel;
	_Public VILabel* SubTextLabel;
	_Public Visindigo::EmphasisSide IconSide;
	_Public bool InverseText;
	_Public QGridLayout* CurrentLayout;
	_Public def_init VIMultiLabel(QWidget* parent = VI_NULL, Visindigo::EmphasisSide iconSide = Visindigo::Left, bool inverseText = false):VIWidget(parent) {
		IconSide = iconSide;
		InverseText = inverseText;
		IconLabel = new VILabel(this);
		TextLabel = new VILabel(this);
		SubTextLabel = new VILabel(this);

		IconLabel->setScaledContents(true);

		CurrentLayout = new QGridLayout(this);
		this->setLayout(CurrentLayout);
		if (IconSide == Visindigo::DefaultEmphasis) { IconSide = Visindigo::Left; }
		switch (IconSide) {
		case Visindigo::Left:
			CurrentLayout->addWidget(IconLabel, 0, 0, 2, 1);
			CurrentLayout->addWidget(SubTextLabel, !InverseText, 1, 1, 1); 
			CurrentLayout->addWidget(TextLabel, InverseText, 1, 1, 1);
			break;
		case Visindigo::Right:
			CurrentLayout->addWidget(IconLabel, 0, 1, 2, 1);
			CurrentLayout->addWidget(SubTextLabel, !InverseText, 0, 1, 1);
			CurrentLayout->addWidget(TextLabel, InverseText, 0, 1, 1);
			break;
		case Visindigo::Top:
			CurrentLayout->addWidget(IconLabel, 0, 0, 1, 1);
			CurrentLayout->addWidget(SubTextLabel, !InverseText + 1, 0, 1, 1);
			CurrentLayout->addWidget(TextLabel, InverseText + 1, 0, 1, 1);
			break;
		case Visindigo::Bottom:
			CurrentLayout->addWidget(IconLabel, 2, 0, 1, 1);
			CurrentLayout->addWidget(SubTextLabel, !InverseText, 0, 1, 1);
			CurrentLayout->addWidget(TextLabel, InverseText, 0, 1, 1);
			break;
		}
	}
};