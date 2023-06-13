﻿#pragma once
#include "../VICore/VICore.h"
#include "VIWidget.h"

class VICodeEdit :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QTextEdit* LineNumberArea;
	_Private QTextEdit* CodeEdit;
	_Private QSyntaxHighlighter* CodeHighlighter;
	_Public QCompleter* CodeCompleter;
	_Private QGraphicsOpacityEffect* LineInfoOpacityEffect;
	_Public def_init VICodeEdit(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		this->setWindowTitle("Visindigo Code Edit");
		LineNumberArea = new QTextEdit(this);
		LineNumberArea->setReadOnly(true);
		LineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		LineNumberArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		LineNumberArea->setAlignment(Qt::AlignRight);
		CodeEdit = new QTextEdit(this);
		CodeEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		CodeEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		LineInfoOpacityEffect = new QGraphicsOpacityEffect(this);
		LineInfoOpacityEffect->setOpacity(0.5);
		connect(CodeEdit->document(), &QTextDocument::blockCountChanged, this, &VICodeEdit::updateLineNumber);
		connect(LineNumberArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &VICodeEdit::scrollEveryEdit);
		connect(CodeEdit->verticalScrollBar(), &QScrollBar::valueChanged, this, &VICodeEdit::scrollEveryEdit);
		connect(CodeEdit->document(), &QTextDocument::cursorPositionChanged, this, &VICodeEdit::debugCursorInfo);
		CodeEdit->setTabStopWidth(4 * QFontMetrics(CodeEdit->font()).width(' '));
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
		CodeEdit->setGeometry(50, 0, this->width()-50, this->height());
	}
	_Public void debugCursorInfo() {
		QTextCursor cursor = CodeEdit->textCursor();
		QString text = "Line: " + QString::number(cursor.blockNumber() + 1) + "\n";
		text += "Column: " + QString::number(cursor.columnNumber() + 1) + "\n";
		text += "Position: " + QString::number(cursor.position() + 1) + "\n";
		//LineInfoArea->setText(text);
		//高亮当前行
		QTextEdit::ExtraSelection selection;
		QColor lineColor = QColor(0,0,0,20);
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