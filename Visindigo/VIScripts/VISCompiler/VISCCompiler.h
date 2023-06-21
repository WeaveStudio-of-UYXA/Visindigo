#pragma once
/*
此文件将VIS词法拆分结果编译到VSEM指令
*/
#include <QtCore>
#include "VISCContentAnalyzer.h"
/*
typedef VISCContentAnalyzer::LineData ContentData;

class VSEMInstructionInfo :public QObject
{
	_Public static QMap<QString, QString> InstructionID;
	_Public static QMap<QString, QString> DeclarationID;
};
#define VSEMInfo_IID VSEMInstructionInfo::InstructionID
#define VSEMInfo_DID VSEMInstructionInfo::DeclarationID
class VISCCompiler :public QObject
{
	Q_OBJECT;
	_Public QList<ContentData> ContentList;
	_Public QStringList VSEMInstruction;
	_Public QStack<int> PartStack;
	_Public QList<ContentData> FunctionContent;
	_Public QStringList FunctionParas;
	_Public bool inFunctionPart;
	_Public void setContentList(QList<ContentData> list) {
		ContentList = list;
	}
	_Public void compile() {
		ContentList.append(ContentData({ 0,{"__END__"} }));
		for (int i = 0; i < ContentList.length(); i++) {
			QStringList content = ContentList[i].Content;
			if (ContentList[i].Indentation < PartStack.top()) {
				VSEMInstruction.append(VSEMInfo_DID["PART_END"]);
				PartStack.pop();
				compileFunction();
				inFunctionPart = false;
				FunctionParas.clear();
			}
			if (inFunctionPart) {
				FunctionContent.append(ContentList[i]);
			}
			if (content[0] == "class") {
				key_class(i, content);
			}
			else if (content[0] == "def") {
				key_def(i, content);
			}
		}
	}
	_Private void key_class(int i, QStringList content) {
		if (content.length() == 3) {
			if (content[2] == ":") {
				PartStack.push(ContentList[i + 1].Indentation);
				VSEMInstruction.append(VSEMInfo_DID["ADD_NAME"] + " " + content[1]);
				VSEMInstruction.append(VSEMInfo_DID["CLASS_START"]);
			}
			else {
				throw std::exception("Class declaration does not end with a colon");
			}
		}
		else if (content.length() == 5) {
			if (content[4] == ":" && content[2] == "extend") {
				PartStack.push(ContentList[i + 1].Indentation);
				VSEMInstruction.append(VSEMInfo_DID["ADD_NAME"] + " " + content[1] + " " + VSEMInfo_DID["EXTEND"] + " " + content[3]);
				VSEMInstruction.append(VSEMInfo_DID["CLASS_START"]);
			}
			else {
				throw std::exception("Class declaration does not end with a colon or keyword 'extend' errors");
			}
		}
		else {
			throw std::exception("Class definition line syntax error: Missing or excessive content");
		}
	}
	_Private void key_def(int i, QStringList content) {
		int len = content.length();
		if (content.length()>=5) {
			if (content[2] == "(" && content[len - 2] == ")" && content[len - 1] == ":") {
				PartStack.push(ContentList[i + 1].Indentation);
				VSEMInstruction.append(VSEMInfo_DID["ADD_NAME"] + " " + content[1]);
				VSEMInstruction.append(VSEMInfo_DID["DEF_START"]);
				inFunctionPart = true;
				FunctionParas = content.mid(3, len - 2);
			}
			else {
				throw std::exception("function definition line syntax error: Incorrect format");
			}
		}
		else {
			throw std::exception("function definition line syntax error: Missing content");
		}
	}
	_Private void compileFunction() {
		QStringList FunctionInstruction;
		QStack<int> ElseStack; 
		QStack<int> IfStack;
		QStack<int> WhileStack;
		QStack<int> ForOutStack;
		QStack<int> ForBackStack;
		for (auto i = FunctionParas.begin(); i != FunctionParas.end(); i++) {
			if (*i != ",") {
				FunctionInstruction.append(QString::number(FunctionInstruction.length()) + " " + VSEMInfo_IID["LOAD_LOCAL_PARA"] + " " + (*i));
			}
		}
		for (auto i = FunctionContent.begin(); i != FunctionContent.end(); i++) {
				contentAnalyzer(&FunctionInstruction, i->Content);
		}
		FunctionInstruction.append(QString::number(FunctionInstruction.length()) + " " + VSEMInfo_IID["RETURN"]);
		VSEMInstruction.append(FunctionInstruction);
	}
	_Private QString contentAnalyzer(QStringList* insList, QStringList code) {
		int signCount = 0;
		if (code.indexOf("(") == -1 && code.indexOf(")") == -1) { //This section is a pure operator merge without parentheses
			
		}
		else { //This means there are function calls or parenthesis operations
			if (code.indexOf("(") == 1 && code.indexOf(")") == code.length() - 1) { //This means that this may be a pure function call
				for (auto i : code) {
				
				}
			}
		}
	}
	_Private bool onlyCommasAndParentheses(QStringList code) {
		for (auto i : code) {
			

		}
	}
};
class LineAnalyzer :public QObject
{
	Q_OBJECT;
};
*/