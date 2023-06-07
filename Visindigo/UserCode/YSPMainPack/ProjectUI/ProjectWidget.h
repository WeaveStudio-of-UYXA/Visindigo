#pragma once
#include "../../../Visindigo/VIWidgets/VIWidgets.h"


class ProjectWidget :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QLabel* TitleLabel;
	_Public def_init ProjectWidget(QWidget* parent = Q_NULLPTR):VIWidget(parent) {
		TitleLabel = new QLabel(this);
		TitleLabel->setText("Yayin Story Player");
	}
};