#pragma once
#include "../VIWidget.h"
#include "../VIWidgetsTransQt.h"
#include "../VISwitchButton.h"
#include "../VIRatioWidget.h"

class VIPublicAPI private_VICodeEdit_FindAndReplaceWidget :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QTextEdit* Master;
	_Private VILabel* TitleLabel;
	_Private VIPushButton* CloseButton;
	_Private VILabel* FindLabel;
	_Private QLineEdit* FindEdit;
	_Private VILabel* ReplaceLabel;
	_Private QLineEdit* ReplaceEdit;
	_Private VILabel* CaseSensitiveLabel;
	_Private VISwitchButton* CaseSensitive;
	_Private VILabel* WholeWordLabel;
	_Private VISwitchButton* WholeWord;
	_Private VIPushButton* FindNext;
	_Private VIPushButton* ReplaceNext;
	_Private VIPushButton* ReplaceAll;
	_Private QGridLayout* CurrentLayout;
	_Public def_init private_VICodeEdit_FindAndReplaceWidget(QTextEdit* master, QWidget* parent);
	//_Public void resizeEvent(QResizeEvent* event)override;
	_Public void onTranslating()override;
};

