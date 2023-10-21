#pragma once
#include "../../VICore/VICore.h"
#include "../VIWidget.h"
#include "VICodeEditUnit.h"

class VIPublicAPI private_VICodeEdit :public QTextEdit
{
	Q_OBJECT;
	_Private QTimer* KeyBoardFreeTimer;
	_Signal void shortcutKey_Find();
	_Signal void keyBoardFree();
	_Signal void lineIndentChanged(quint32 line, quint32 indentLevel);
	_Signal void saveNeeded(bool saveAs);
	_Public def_init private_VICodeEdit(QWidget* parent = Q_NULLPTR);
	_Public void keyPressEvent(QKeyEvent* event) override;
	_Private void keyPressEvent_Tab(QKeyEvent* event);
	_Private void keyPressEvent_BackTab(QKeyEvent* event);
	_Private void keyPressEvent_Return(QKeyEvent* event);
	_Private void keyPressEvent_V(QKeyEvent* event); // ctrl + v, paste without format (override raw)
	_Private void keyPressEvent_S(QKeyEvent* event); // ctrl + s, save file
	_Private void keyPressEvent_R(QKeyEvent* event); // ctrl + r, save as file
};

class VIPublicAPI VICodeEdit :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void languageTypeChanged(const QString& typeName);
	_Signal void cursorPositionChanged(int line, int column, int position, const QString& lineText);
	VI_PrivateProperty(quint32, CurrentLineCount);
	_Private QTextEdit* LineNumberArea;
	_Private private_VICodeEdit* CodeEdit;
	_Private QTextBrowser* LineInfoArea;
	_Private QSyntaxHighlighter* CodeHighlighter;
	_Public QCompleter* CodeCompleter;
	_Private QString LanguageType;
	_Private QString FilePath;
	VI_PrivateProperty(bool, needSave);
	_Private private_VICodeEdit_FindAndReplaceWidget* FindAndReplaceWidget = VI_NULL;
	_Public def_init VICodeEdit(QWidget* parent = VI_NULL);
	_Private void cursorInfoGenerator();
	_Public bool eventFilter(QObject* tar, QEvent* eve);
	_Public bool openFile(const QString& filePath);
	_Public bool saveFile(const QString& filePath = "");
	_Public void save(bool saveAs = false);
	_Private void closeEvent(QCloseEvent* event) override;
	_Public bool find(const QString& substr, QTextDocument::FindFlags flags);
	_Public void showFindAndReplaceWidget();
	_Public void setFont(const QFont& font);
	_Public void setCodeSyntaxHighlighter(QSyntaxHighlighter* highlighter);
	_Public void resizeEvent(QResizeEvent* event);
	_Public void debugCursorInfo();
	_Public void mousePressEvent(QMouseEvent* event);
	_Public void scrollEveryEdit(int value);
	_Public void updateLineNumber();
	_Private void updateLineInfoArea(quint32 line, quint32 indentLevel);
	_Private static QString getIndentNotice(quint32 indentLevel);
};

class VIPublicAPI private_VIMultiCodeEdit_DocLabel :public VIAbstractRatioWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Private VILabel* TypeIconLabel;
	_Private VILabel* DocNameLabel;
	_Private VICodeEdit* CodeEdit; // that is to say, this label class also works as a container
};

class VICodeEditTestWidget :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Private VICodeEdit* CodeEdit;
	_Private QGridLayout* Layout;
	_Public def_init VICodeEditTestWidget(QWidget* parent = VI_NULL) :VIWidget(parent) {
		CodeEdit = new VICodeEdit(this);
		Layout = new QGridLayout(this);
		Layout->addWidget(CodeEdit);
		this->setLayout(Layout);
		this->setMinimumSize(800, 600);
	}
};