#pragma once
#include "VIWidget.h"

//PSOD -> Purple Screen Of Death
class VIPublicAPI VIPSOD :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Private QLabel* EmojiLabel;
	_Private QLabel* TitleLabel;
	_Private QLabel* TypeLabel;
	_Private QLabel* ReasonLabel;
	_Private QLabel* HelpLabel;
	_Private QGridLayout* CurrentLayout;
	_Public def_init VIPSOD(VIException& error) {
		this->setWindowTitle("Visindigo PSOD");
		EmojiLabel = new QLabel(this);
		EmojiLabel->setText("(；′⌒`)");
		EmojiLabel->setStyleSheet("QLabel{font-size:100px}");
		TitleLabel = new QLabel(this);
		TitleLabel->setText("Your Visindigo framework or the application running on it has encountered a fatal error. \
\nWe have listed the basic information below, and you can use it to consult with developers. \
\nYou can restart the program yourself later");
		TitleLabel->setStyleSheet("QLabel{font-size:20px}");
		TypeLabel = new QLabel(this);
		TypeLabel->setText("Exception Type: "+error.getExceptionName());
		TypeLabel->setStyleSheet("QLabel{font-size:30px}");
		ReasonLabel = new QLabel(this);
		ReasonLabel->setText("Exception Reason: "+error.getReason());
		ReasonLabel->setStyleSheet("QLabel{font-size:20px}");
		HelpLabel = new QLabel(this);
		HelpLabel->setText("Help: "+error.getHelp());
		HelpLabel->setStyleSheet("QLabel{font-size:20px}");
#ifdef WINDOWS_DEPLOY
		this->setStyleSheet("QWidget{background-color:#DF81E8;color:#FFFFFF;font-family:'Microsoft Yahei'}");
#else
		this->setStyleSheet("QWidget{background-color:#DF81E8;color:#FFFFFF;font-family:'SimHei'}");
#endif
		CurrentLayout = new QGridLayout(this);
		this->setLayout(CurrentLayout);
		CurrentLayout->addWidget(EmojiLabel, 0, 0, 1, 1);
		CurrentLayout->addWidget(TitleLabel, 1, 0, 1, 1);
		CurrentLayout->addWidget(TypeLabel, 2, 0, 1, 1);
		CurrentLayout->addWidget(ReasonLabel, 3, 0, 1, 1);
		CurrentLayout->addWidget(HelpLabel, 4, 0, 1, 1);
		this->setMinimumSize(800, 600);
		this->show();
	}
};