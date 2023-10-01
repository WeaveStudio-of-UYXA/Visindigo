#pragma once
#include "../../VICore/VICore.h"
#include "../VIWidget.h"

class VIPublicAPI private_VICodeEdit :public QTextEdit
{
	Q_OBJECT;
	_Public def_init private_VICodeEdit(QWidget* parent = Q_NULLPTR) :QTextEdit(parent) {
		this->setTabStopWidth(4 * QFontMetrics(this->font()).width(' '));
	}
	_Public void keyPressEvent(QKeyEvent* event) override {
		if (event->key() == Qt::Key_Tab) {
			//if cursor is not in selection
			if (!textCursor().hasSelection()) {
				//if the text before is empty, insert 4 spaces, else insert a tab
				QTextCursor cursor = textCursor();
				cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
				QString lineText = cursor.selectedText();
				for (auto i : lineText) {
					if (i != ' ' && i != '\t') {
						insertPlainText("\t");
						return;
					}
				}
				insertPlainText("    ");
				return;
			}
			else {
				//if cursor is in selection, insert 4 spaces before every line, no matter how many lines are selected
				QTextCursor cursor = textCursor();
				//get the selection start
				int startPosition = cursor.selectionStart();
				int endPosition = cursor.selectionEnd();
				//get the start line and end line
				int startLine = document()->findBlock(startPosition).blockNumber();
				int endLine = document()->findBlock(endPosition).blockNumber();
				cursor.setPosition(startPosition);
				cursor.movePosition(QTextCursor::StartOfLine);
				int fixStartPos = cursor.position();
				//add 4 spaces before every line
				for (int i = startLine; i <= endLine; i++) {
					cursor.movePosition(QTextCursor::StartOfLine);
					cursor.insertText("    ");
					cursor.movePosition(QTextCursor::Down);
				}
				cursor.setPosition(fixStartPos, QTextCursor::KeepAnchor);
				return;
			}
		}
		if (event->key() == Qt::Key_Backtab) {
			if (!textCursor().hasSelection()) {
				//if the text before is empty, remove 4 spaces, else do nothing
				qDebug() << "Shift+Tab";
				QTextCursor cursor = textCursor();
				cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
				QString lineText = cursor.selectedText();
				int removeCharCount = 0;
				for (auto i : lineText) {
					if (i != ' ' && i != '\t') {
						return;
					}
				}
				for (auto i : lineText) {
					if (i == ' ') {
						removeCharCount++;
					}
					else if (i == '\t') {
						removeCharCount += 4;
					}
					if (removeCharCount >= 4) {
						removeCharCount = 4;
						break;
					}
				}
				for (int i = 0; i < removeCharCount; i++) {
					textCursor().deletePreviousChar();
				}
				return;
			}
			else {
				//if cursor is in selection, insert 4 spaces before every line, no matter how many lines are selected
				QTextCursor cursor = textCursor();
				//get the selection start
				int startPosition = cursor.selectionStart();
				int endPosition = cursor.selectionEnd();
				//get the start line and end line
				int startLine = document()->findBlock(startPosition).blockNumber();
				int endLine = document()->findBlock(endPosition).blockNumber();
				cursor.setPosition(startPosition);
				cursor.movePosition(QTextCursor::StartOfLine);
				int fixStartPos = cursor.position();
				//add 4 spaces before every line
				for (int i = startLine; i <= endLine; i++) {
					cursor.movePosition(QTextCursor::StartOfLine);
					cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
					QString lineText = cursor.selectedText();
					int removeCharCount = 0;
					for (auto i : lineText) {
						if (i == ' ') {
							removeCharCount++;
						}
						else if (i == '\t') {
							removeCharCount += 4;
						}
						else {
							break;
						}
						if (removeCharCount >= 4) {
							removeCharCount = 4;
							break;
						}
					}
					cursor.movePosition(QTextCursor::StartOfLine);
					for (int i = 0; i < removeCharCount; i++) {
						cursor.deleteChar();
					}
					cursor.movePosition(QTextCursor::Down);
				}
				cursor.setPosition(fixStartPos, QTextCursor::KeepAnchor);
				return;
			}
		}
		if (event->key() == Qt::Key_Return) {
			//get the text of current line
			QTextCursor cursor = textCursor();
			cursor.movePosition(QTextCursor::StartOfLine);
			cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
			QString lineText = cursor.selectedText();
			//get the number of spaces at the beginning of the line
			int spaceCount = 0;
			for (int i = 0; i < lineText.size(); i++) {
				if (lineText[i] == ' ') {
					spaceCount++;
				}
				else {
					break;
				}
			}
			//create a new line and insert spaces
			insertPlainText("\n");
			for (int i = 0; i < spaceCount; i++) {
				insertPlainText(" ");
			}
			return ;
		}
		QTextEdit::keyPressEvent(event);
	}
};
class VIPublicAPI VICodeEdit :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QTextEdit* LineNumberArea;
	_Private private_VICodeEdit* CodeEdit;
	_Private QSyntaxHighlighter* CodeHighlighter;
	_Public QCompleter* CodeCompleter;
	_Public def_init VICodeEdit(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		this->setWindowTitle("Visindigo Code Edit");
		QFont font = QFont("Microsoft YaHei");

		LineNumberArea = new QTextEdit(this);
		LineNumberArea->setReadOnly(true);
		LineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		LineNumberArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		LineNumberArea->setAlignment(Qt::AlignRight);
		LineNumberArea->setFont(font);
		CodeEdit = new private_VICodeEdit(this);
		CodeEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		CodeEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		//关闭自动换行
		CodeEdit->setLineWrapMode(QTextEdit::NoWrap);
		CodeEdit->setFont(font);
		connect(CodeEdit->document(), &QTextDocument::blockCountChanged, this, &VICodeEdit::updateLineNumber);
		connect(LineNumberArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &VICodeEdit::scrollEveryEdit);
		connect(CodeEdit->verticalScrollBar(), &QScrollBar::valueChanged, this, &VICodeEdit::scrollEveryEdit);
		connect(CodeEdit->document(), &QTextDocument::cursorPositionChanged, this, &VICodeEdit::debugCursorInfo);
		this->setStyleSheet("QWidget{background-color:#202020;color:#FFFFFF}");
		CodeCompleter = new QCompleter(this);
		CodeCompleter->setWidget(CodeEdit);
		CodeCompleter->setCompletionMode(QCompleter::PopupCompletion);
		CodeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
		CodeCompleter->setWrapAround(false);
		CodeCompleter->setModel(new QStringListModel(this));
		CodeCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
	}
	_Public void setFont(const QFont& font) {
		LineNumberArea->setFont(font);
		CodeEdit->setFont(font);
		CodeEdit->setTabStopWidth(4 * QFontMetrics(CodeEdit->font()).width(' '));
	}
	_Public void setCodeSyntaxHighlighter(QSyntaxHighlighter* highlighter) {
		CodeHighlighter = highlighter;
		CodeHighlighter->setDocument(CodeEdit->document());
	}
	_Public void resizeEvent(QResizeEvent* event) {
		LineNumberArea->setGeometry(0, 0, 50, this->height());
		CodeEdit->setGeometry(50, 0, this->width() - 50, this->height());
	}
	_Public void debugCursorInfo() {
		QTextCursor cursor = CodeEdit->textCursor();
		QString text = "Line: " + QString::number(cursor.blockNumber() + 1) + "\n";
		text += "Column: " + QString::number(cursor.columnNumber() + 1) + "\n";
		text += "Position: " + QString::number(cursor.position() + 1) + "\n";
		//LineInfoArea->setText(text);
		//高亮当前行
		QTextEdit::ExtraSelection selection;
		QColor lineColor = QColor(0, 0, 0, 20);
		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = CodeEdit->textCursor();
		selection.cursor.clearSelection();
		CodeEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>() << selection);
	}
	_Public void mousePressEvent(QMouseEvent* event) {
		if (event->button() == Qt::LeftButton) {
			QTextCursor cursor = CodeEdit->cursorForPosition(event->pos());
			CodeEdit->setTextCursor(cursor);
			CodeEdit->setFocus();
		}
	}
	_Public void scrollEveryEdit(int value) {
		LineNumberArea->verticalScrollBar()->setValue(value);
		CodeEdit->verticalScrollBar()->setValue(value);
	}
	_Public void updateLineNumber() {
		QString text = "<p align=\"right\">";
		for (int i = 1; i <= CodeEdit->document()->blockCount(); i++) {
			text += QString::number(i) + "<br>";
		}
		text += "</p>";
		LineNumberArea->setText(text);
		text = "<p align=\"left\">";
		for (int i = 1; i <= CodeEdit->document()->blockCount(); i++) {
			text += QString::number(i) + " Debug Info Text<br>";
		}
		text += "</p>";
		LineNumberArea->verticalScrollBar()->setRange(CodeEdit->verticalScrollBar()->minimum(), CodeEdit->verticalScrollBar()->maximum());
		LineNumberArea->verticalScrollBar()->setValue(CodeEdit->verticalScrollBar()->value());
	}
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