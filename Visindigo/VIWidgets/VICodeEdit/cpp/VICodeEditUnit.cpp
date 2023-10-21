#include "../VICodeEditUnit.h"

def_init private_VICodeEdit_FindAndReplaceWidget::private_VICodeEdit_FindAndReplaceWidget(QTextEdit* master, QWidget* parent) :VIWidget(parent) {
	Master = master;
	TitleLabel = new VILabel(this);
	CloseButton = new VIPushButton(this);
	FindLabel = new VILabel(this);
	FindEdit = new QLineEdit(this);
	ReplaceLabel = new VILabel(this);
	ReplaceEdit = new QLineEdit(this);
	CaseSensitiveLabel = new VILabel(this);
	CaseSensitive = new VISwitchButton(this);
	WholeWordLabel = new VILabel(this);
	WholeWord = new VISwitchButton(this);
	FindNext = new VIPushButton(this);
	ReplaceNext = new VIPushButton(this);
	ReplaceAll = new VIPushButton(this);
	CloseButton->setText("X");// stupid but works
	connect(CloseButton, &QPushButton::clicked, this, &private_VICodeEdit_FindAndReplaceWidget::hide);
	/*
	| Title | | Close |
	| FindLabel | FindEdit | - |
	| ReplaceLabel | ReplaceEdit | - |
	| CaseSensitiveLabel | |CaseSensitive |
	| WholeWordLabel | |WholeWord |
	| FindNext | ReplaceNext | ReplaceAll |
	*/
	CurrentLayout = new QGridLayout(this);
	CurrentLayout->addWidget(TitleLabel, 0, 0, 1, 1);
	CurrentLayout->addWidget(CloseButton, 0, 2, 1, 1);
	CurrentLayout->addWidget(FindLabel, 1, 0, 1, 1);
	CurrentLayout->addWidget(FindEdit, 1, 1, 1, 2);
	CurrentLayout->addWidget(ReplaceLabel, 2, 0, 1, 1);
	CurrentLayout->addWidget(ReplaceEdit, 2, 1, 1, 2);
	CurrentLayout->addWidget(CaseSensitiveLabel, 3, 0, 1, 1);
	CurrentLayout->addWidget(CaseSensitive, 3, 2, 1, 1);
	CurrentLayout->addWidget(WholeWordLabel, 4, 0, 1, 1);
	CurrentLayout->addWidget(WholeWord, 4, 2, 1, 1);
	CurrentLayout->addWidget(FindNext, 5, 0, 1, 1);
	CurrentLayout->addWidget(ReplaceNext, 5, 1, 1, 1);
	CurrentLayout->addWidget(ReplaceAll, 5, 2, 1, 1);
	CurrentLayout->setSpacing(2);
	CurrentLayout->setContentsMargins(2, 2, 2, 2);
	VisindigoWidgets::PackageMeta::getInstance()->addTranslatableObject(this);
	onTranslating();
}

void private_VICodeEdit_FindAndReplaceWidget::onTranslating() {
	TitleLabel->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_Title"));
	FindLabel->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_Find"));
	ReplaceLabel->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_Replace"));
	CaseSensitiveLabel->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_CaseSensitive"));
	WholeWordLabel->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_WholeWord"));
	FindNext->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_FindNext"));
	ReplaceNext->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_ReplaceNext"));
	ReplaceAll->setText(getTranslation("Widgets_CodeEdit_FindAndReplace_ReplaceAll"));
}