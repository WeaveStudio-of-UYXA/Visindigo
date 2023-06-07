#pragma once
#include "../../../Visindigo/VICore/VICore.h"
#include "../../../Visindigo/VIWidgets/VIWidgets.h"
#include <QtGui>

class SPSHighlighter :public QSyntaxHighlighter, public VIBaseObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QStringList UserClassNames;
	_Public QStringList UserFunctionNames;
	_Public QStringList UserVariableNames;
	_Public VICodeEdit* CodeEdit;
	_Public def_init SPSHighlighter(QTextDocument* doc) :QSyntaxHighlighter(doc) {}
	_Public void highlightBlock(const QString& text) override {
		qDebug() << "Highlighting:" << text;
		setFormat(0, text.length(), Qt::black);
		setCurrentBlockState(0);
		userName(text);
		spsKeyword(text);
		singleLineComment(text);
		multiLineComment(text);
		SPOLSingleLine(text);
	}
	_Public void spsKeyword(const QString& text) {
		QTextCharFormat stringFormat;
		stringFormat.setForeground(Qt::GlobalColor::darkYellow);
		QRegExp string("\"[^\"]*\"");
		int index = text.indexOf(string);
		while (index >= 0) {
			int length = string.matchedLength();
			setFormat(index, length, stringFormat);
			index = text.indexOf(string, index + length);
		}

		QTextCharFormat numberFormat;
		numberFormat.setForeground(Qt::green);
		QRegExp number("\\b[0-9]+\\b");
		index = text.indexOf(number);
		while (index >= 0) {
			int length = number.matchedLength();
			setFormat(index, length, numberFormat);
			index = text.indexOf(number, index + length);
		}

		QTextCharFormat keywordFormat;
		keywordFormat.setForeground(Qt::blue);
		QRegExp keyword("\\b(var|let|const|if|else|for|while|do|break|continue|return|function|class|new|this|super|switch|case|default|try|catch|finally|throw|import|export|from|as|in|of|instanceof|typeof|void|delete|true|false|null|undefined)\\b");
		index = text.indexOf(keyword);
		while (index >= 0) {
			int length = keyword.matchedLength();
			setFormat(index, length, keywordFormat);
			index = text.indexOf(keyword, index + length);
		}

	}
	_Public void singleLineComment(const QString& text) {
		QTextCharFormat commentFormat;
		commentFormat.setForeground(Qt::red);
		//提取//之后的所有内容
		QRegExp comment("//[^\n]*");
		//保存到UserFunctionNames
		int index = text.indexOf(comment);
		while (index >= 0) {
			int length = comment.matchedLength();
			setFormat(index, length, commentFormat);
			index = text.indexOf(comment, index + length);
		}
	}
	_Public void userName(const QString& text) {
		//提取所有函数名称
		//提取function之后的名称
		QRegExp function("\\bfunction\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\b");
		//保存到UserFunctionNames
		int index = text.indexOf(function);
		while (index >= 0) {
			int length = function.matchedLength();
			QString funcName = function.cap(1);
			if (!UserClassNames.contains(funcName)) UserFunctionNames.append(funcName);
			index = text.indexOf(function, index + length);
		}
		//提取class或new之后的名称
		QRegExp _class("\\b(class|new)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\b");
		//保存到UserClassNames
		index = text.indexOf(_class);
		while (index >= 0) {
			int length = _class.matchedLength();
			QString className = _class.cap(2);
			if (!UserFunctionNames.contains(className)) UserClassNames.append(className);
			index = text.indexOf(className, index + length);
		}
		//提取左括号之前 
		//且 不是new或class之后的名称
		QRegExp name("\\b([a-zA-Z_][a-zA-Z0-9_]*)\\s*\\(");
		//保存到UserFunctionNames
		index = text.indexOf(name);
		while (index >= 0) {
			int length = name.matchedLength();
			QString funcName = name.cap(1);
			if (!UserClassNames.contains(funcName) && !UserFunctionNames.contains(funcName)) {
				UserFunctionNames.append(funcName);
			}
			index = text.indexOf(name, index + length);
		}
		//提取点（若有）至等号之间的名称
		QRegExp variable("\\.([a-zA-Z_][a-zA-Z0-9_]*)\\s*=");
		//保存到UserVariableNames
		index = text.indexOf(variable);
		while (index >= 0) {
			int length = variable.matchedLength();
			QString varName = variable.cap(1);
			if (!UserClassNames.contains(varName) && !UserFunctionNames.contains(varName) && !UserVariableNames.contains(varName)) {
				UserVariableNames.append(varName);
			}
			index = text.indexOf(variable, index + length);
		}
		//提取点之前的名称
		QRegExp variable2("([a-zA-Z_][a-zA-Z0-9_]*)\\s*\\.");
		//保存到UserVariableNames
		index = text.indexOf(variable2);
		while (index >= 0) {
			int length = variable2.matchedLength();
			QString varName = variable2.cap(1);
			if (!UserClassNames.contains(varName) && !UserFunctionNames.contains(varName) && !UserVariableNames.contains(varName)) {
				UserVariableNames.append(varName);
			}
			index = text.indexOf(variable2, index + length);
		}
		//提取var或let或const之后的名称
		QRegExp var("\\b(var|let|const)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\b");
		//保存到UserVariableNames
		index = text.indexOf(var);
		while (index >= 0) {
			int length = var.matchedLength();
			QString varName = var.cap(2);
			UserVariableNames.append(varName);
			index = text.indexOf(var, index + length);
		}
		//为三个列表中的单词着色
		QTextCharFormat userFunctionFormat;
		userFunctionFormat.setForeground(Qt::darkMagenta);
		QTextCharFormat userClassFormat;
		userClassFormat.setForeground(Qt::darkGreen);
		QTextCharFormat userVariableFormat;
		userVariableFormat.setForeground(Qt::darkRed);
		for (int i = 0; i < UserFunctionNames.size(); i++) {
			QString pattern = "\\b" + UserFunctionNames.at(i) + "\\b";
			QRegExp userFunction(pattern);
			index = text.indexOf(userFunction);
			while (index >= 0) {
				int length = userFunction.matchedLength();
				setFormat(index, length, userFunctionFormat);
				index = text.indexOf(userFunction, index + length);
			}
		}
		for (int i = 0; i < UserClassNames.size(); i++) {
			QString pattern = "\\b" + UserClassNames.at(i) + "\\b";
			QRegExp userClass(pattern);
			index = text.indexOf(userClass);
			while (index >= 0) {
				int length = userClass.matchedLength();
				setFormat(index, length, userClassFormat);
				index = text.indexOf(userClass, index + length);
			}
		}
		for (int i = 0; i < UserVariableNames.size(); i++) {
			QString pattern = "\\b" + UserVariableNames.at(i) + "\\b";
			QRegExp userVariable(pattern);
			index = text.indexOf(userVariable);
			while (index >= 0) {
				int length = userVariable.matchedLength();
				setFormat(index, length, userVariableFormat);
				index = text.indexOf(userVariable, index + length);
			}
		}
	}
	_Public void multiLineComment(const QString& text) {
		QTextCharFormat multiLineCommentFormat;
		multiLineCommentFormat.setForeground(Qt::red);
		QTextCharFormat spolCommentFormat;
		spolCommentFormat.setForeground(Qt::darkGreen);
		//初始条件为/*但不能是/*SPOL
		QRegularExpression startExpression("/\\*(?!SPOL)");
		//结束条件为*/
		QRegularExpression endExpression("\\*/");
		//初始条件为/*SPOL
		QRegularExpression spolStartExpression("/\\*SPOL");

		int startIndex = 0;
		if (previousBlockState() != 2 && previousBlockState() != 3) {
			startIndex = text.indexOf(startExpression);
			if (startIndex < 0) {
				startIndex = text.indexOf(spolStartExpression);
				if (startIndex >= 0) { setCurrentBlockState(3); }
			}
			else { setCurrentBlockState(2); }
		}
		while (startIndex >= 0) {
			QRegularExpressionMatch endMatch;
			int endIndex = text.indexOf(endExpression, startIndex, &endMatch);
			int commentLength;
			if (endIndex == -1) {
				if (currentBlockState() == 0&& previousBlockState() != 1) {
					setCurrentBlockState(previousBlockState());
				}
				commentLength = text.length() - startIndex;
			}
			else {
				if (currentBlockState() == 0) { setCurrentBlockState(1);}
				commentLength = endIndex - startIndex + endMatch.capturedLength();
			}
			if (currentBlockState() == 2 || currentBlockState() == 1 && previousBlockState() == 2) {
				setFormat(startIndex, commentLength, multiLineCommentFormat);
			}
			else if (currentBlockState() == 3 || currentBlockState() == 1 && previousBlockState() == 3) {
				setFormat(startIndex, commentLength, spolCommentFormat);
			}
			startIndex = text.indexOf(startExpression, startIndex + commentLength);
		}
	}
	_Public void SPOLSingleLine(const QString& text) {
		if (currentBlockState() == 3) {
			if (text.startsWith("/SPOL")) {
				//Version
				QTextCharFormat spolVersionLine;
				spolVersionLine.setForeground(Qt::darkMagenta);
				setFormat(0, text.length(), spolVersionLine);
			}
			else if (text.startsWith("-->")) {
				//Tag
				QTextCharFormat spolTagLine;
				spolTagLine.setBackground(Qt::yellow);
				spolTagLine.setForeground(Qt::black);
				setFormat(0, text.length(), spolTagLine);
			}
			else if (text.startsWith(">>>")) {
				//Speak
				QTextCharFormat spolSpeakLine;
				spolSpeakLine.setBackground(Qt::lightGray);
				spolSpeakLine.setForeground(Qt::darkBlue);
				setFormat(0, text.length(), spolSpeakLine);
			}
			
		}
	}
};
class SPSEditor :public VIWidget {
	Q_OBJECT;
	VI_OBJECT;
	VI_Property(QTextEdit*, TextEdit);
	VI_Property(VICodeEdit*, CodeEdit)
	VI_Property(SPSHighlighter*, Highlighter);
	VI_Property(QGridLayout*, CurrentLayout);
	_Public def_init SPSEditor(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		TextEdit = new QTextEdit(this);
		TextEdit->setGeometry(0, 0, 800, 600);
		TextEdit->show();
		TextEdit->setFont(QFont("Microsoft YaHei", 12));
		//指定Tab宽为实际字符宽度的四个
		TextEdit->setTabStopWidth(4 * QFontMetrics(TextEdit->font()).width(' '));
		Highlighter = new SPSHighlighter(TextEdit->document());
		connect(TextEdit->document(), &QTextDocument::blockCountChanged, this, &SPSEditor::debugLineNum);
		CurrentLayout = new QGridLayout(this);
		//CurrentLayout->addWidget(TextEdit);
		CodeEdit = new VICodeEdit(this);
		CodeEdit->setFont(QFont("Microsoft YaHei", 12));
		CodeEdit->setCodeSyntaxHighlighter(Highlighter);
		CurrentLayout->addWidget(CodeEdit);
		Highlighter->CodeEdit = CodeEdit;
		this->setMinimumSize(800, 600);
	}
	_Slot void debugLineNum(int num) {
		qDebug()<< num;
	}
};