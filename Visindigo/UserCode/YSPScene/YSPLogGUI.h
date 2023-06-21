#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "../../Visindigo/VIWidgets/VIWidgets.h"

class YSPLogGUI :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public QTextBrowser* Browser;
	_Public VIPushButton* ExitButton;
	_Public def_init YSPLogGUI(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		
	}
};
