#pragma once
/*
此文件提供VIS的词法拆分器
此拆分仅将源码中的标识符、符号等拆开、刨去单行注释
不对多行注释有处理。
*/
#include <QtCore>
#include "../../VICore/macro/VIMarco.h"
#include <iostream>
#include "VISCContentType.h"
#include <exception>
//#define Erase_Useless_Word

#define ifContent(name, type, stype) \
if (content->Content == name) \
{\
if (Erase_Useless_Word) { content->Content = ""; } \
content->ContentType = VISContentInfo::VIS_ContentType::type; \
content->SpecificContentType = VISContentInfo::VIS_SpecificContentType::stype; \
return;\
}

class VISCContentAnalyzer :public QObject
{
	Q_OBJECT;
	_Public FileContentData FileContent;
	_Public def_init VISCContentAnalyzer(QObject* parent = VI_NULLPTR) :QObject(parent) {};
	_Public def_del ~VISCContentAnalyzer() {};
	_Public static LineContentData lineContentSplitter(QString rawCode, bool Erase_Useless_Word = true) {
		int blankNum = 0;
		LineContentData lineData;
		for (auto i = rawCode.begin(); i != rawCode.end(); i++) {
			if (*i == ' ') { blankNum++; continue; }
			else {
				i++;
				if (i != rawCode.end()) {
					if (*i == '@') {
						lineData.Indentation = blankNum;
						lineData.ContentDataList.append(
							ContentData{ "", VISContentInfo::VIS_ContentType::SYMBOL, VISContentInfo::VIS_SpecificContentType::AT });
						QString rawLine = rawCode.mid(i - rawCode.begin() + 1);
						lineData.ContentDataList.append(
							ContentData{ rawLine, VISContentInfo::VIS_ContentType::CONST_STR, VISContentInfo::VIS_SpecificContentType::CONST_STR});
						return lineData;
					}
				}
				break;
			}
		}
		lineData.Indentation = blankNum;
		QString element = "";
		QStringList elementsRaw;
		bool isString = false;
		bool behindBackSlash = false;
		bool BlankTermination = false;
		for (auto i = rawCode.begin(); i != rawCode.end(); i++) {
			if ((*i) == "\\" && !behindBackSlash) {
				behindBackSlash = true;
				continue;
			}
			if ((*i) == "\"" && !behindBackSlash) {
				isString = !isString;
			}
			if (!isString) {
				if ((*i) == "#") {
					break;
				}
				if (((*i).isLetterOrNumber() && !(*i).isSpace())||(*i)=="."||(*i)=="_"||(*i)=="\"") {
					element.append(*i);
				}
				else {
					if (element != " " && element != "") {
						elementsRaw.append(element);
					}
					if (*i != " " && *i != "") {
						elementsRaw.append(*i);
					}
					element.clear();
				}
			}
			else {
				element.append(*i);
			}
			behindBackSlash = false;
		}
		if (element != " " && element != "") {
			elementsRaw.append(element);
		}
		//qDebug() << elementsRaw.join(" ");
		QStringList content;
		bool lastNotAppend = false;
		if (elementsRaw.length() == 1) {
			content = elementsRaw;
		}
		for (int i = 0; i < elementsRaw.length() - 1; i++) {
			QString c = elementsRaw[i];
			QString n = elementsRaw[i + 1];
			if (c==n&&c!="("&&c!=")"&&c!="["&&c!="]"&&c!="{"&&c!="}"&&c.size()==1&&(!c[0].isLetterOrNumber())) {
				content.append(c+c);
				i++;
			}
			else if ((c == "+" || c == "-" || c == "*" || c == "/" || c == "!" || c==">" || c=="<") && n == "=") {
				content.append(elementsRaw[i] + elementsRaw[i + 1]);
				i++;
			}
			else if (c == "-" && n == ">") {
				content.append(elementsRaw[i] + elementsRaw[i + 1]);
				i++;
			}
			else {
				content.append(elementsRaw[i]);
				if ( i == elementsRaw.length() - 2) { lastNotAppend = true; }
			}
		}
		if (lastNotAppend) { content.append(elementsRaw.last()); }
		for (auto i = content.begin(); i != content.end(); i++) {
			ContentData ctD = { *i, VISContentInfo::VIS_ContentType::UNKNOWN, VISContentInfo::VIS_SpecificContentType::UNKNOWN };
			lineData.ContentDataList.append(ctD);
		}
		for (auto i = lineData.ContentDataList.begin(); i != lineData.ContentDataList.end(); i++) {
			try {
				contentAnalysis(&(*i), Erase_Useless_Word);
			}
			catch (std::exception e) {
				qDebug() << e.what();
			}
		}
		return lineData;
	}
	_Private static void contentAnalysis(ContentData* content, bool Erase_Useless_Word = true) {
		ifContent("var", KEYWORD, VAR);
		ifContent("def", KEYWORD, DEF); ifContent("fn", KEYWORD, DEF); ifContent("function", KEYWORD, DEF);
		ifContent("class", KEYWORD, CLASS);
		ifContent("true", KEYWORD, _TRUE); ifContent("True", KEYWORD, _TRUE); ifContent("TRUE", KEYWORD, _TRUE);
		ifContent("false", KEYWORD, _FALSE); ifContent("False", KEYWORD, _FALSE); ifContent("FALSE", KEYWORD, _FALSE);
		ifContent("null", KEYWORD, _None); ifContent("Null", KEYWORD, _None); ifContent("NULL", KEYWORD, _None);
		ifContent("None", KEYWORD, _None); ifContent("none", KEYWORD, _None); ifContent("NONE", KEYWORD, _None);
		ifContent("new", KEYWORD, NEW);
		ifContent("del", KEYWORD, DEL); ifContent("delete", KEYWORD, DEL);
		
		ifContent("if", KEYWORD, IF); ifContent("elif", KEYWORD, ELIF); ifContent("else", KEYWORD, ELSE);

		ifContent("while", KEYWORD, WHILE); ifContent("for", KEYWORD, FOR);
		ifContent("continue", KEYWORD, CONTINUE); ifContent("break", KEYWORD, BREAK);

		ifContent("catch", KEYWORD, CATCH); 
		ifContent("throw", KEYWORD, THROW); ifContent("raise", KEYWORD, THROW);
		ifContent("try", KEYWORD, TRY);

		ifContent("switch", KEYWORD, SWITCH); ifContent("match", KEYWORD, SWITCH);
		ifContent("case", KEYWORD, CASE);

		ifContent("return", KEYWORD, RETURN);
		ifContent("this", KEYWORD, _THIS); ifContent("self", KEYWORD, _THIS);
		ifContent("super", KEYWORD, SUPER);

		ifContent("not", KEYWORD, NOT); ifContent("and", KEYWORD, AND); ifContent("or", KEYWORD, OR);

		ifContent("is", KEYWORD, IS); ifContent("in", KEYWORD, _IN);
		if (VISContentInfo::KeywordForbidden.contains(content->Content)) {
			qDebug() << "VISCContentAnalyzer has found a prohibited keyword:";
			qDebug() << content->Content;
			throw std::exception("Keyword Forbidden");
		}
		ifContent("+", SYMBOL, ADD); ifContent("-", SYMBOL, SUB); ifContent("*", SYMBOL, MUL); ifContent("/", SYMBOL, DIV);
		ifContent("%", SYMBOL, MOD); 

		ifContent(">", SYMBOL, MORE); ifContent("<", SYMBOL, LESS); ifContent("==", SYMBOL, EQUAL);
		ifContent(">=", SYMBOL, NOTLE); ifContent("<=", SYMBOL, NOTMO); ifContent("!=", SYMBOL, NOTEQ);

		ifContent("=", SYMBOL, ASSIGN); ifContent(",", SYMBOL, COMMA); 
		ifContent(":", SYMBOL, COLON); ifContent("->", SYMBOL, ARROW); 

		ifContent("++", SYMBOL, IMAO); ifContent("--", SYMBOL, IMSO); 
		ifContent("**", SYMBOL, POWER); ifContent("//", SYMBOL, RADICAL);

		ifContent("+=", SYMBOL, IMADD); ifContent("-=", SYMBOL, IMSUB); 
		ifContent("*=", SYMBOL, IMMUL); ifContent("/=", SYMBOL, IMDIV);

		ifContent("(", SYMBOL, LPAR); ifContent(")", SYMBOL, RPAR); 
		ifContent("[", SYMBOL, LBKT);  ifContent("]", SYMBOL, RBKT);
		ifContent("{", SYMBOL, LBRC); ifContent("}", SYMBOL, RBRC);

		if (VISContentInfo::SymbolForbidden.contains(content->Content)) {
			qDebug() << "VISCContentAnalyzer has found a prohibited symbol:";
			qDebug() << content->Content;
			throw std::exception("Symbol Forbidden");
		}
		if (content->Content[0] == "\"" && content->Content[content->Content.length() - 1] == "\"") {
			content->ContentType = VISContentInfo::VIS_ContentType::CONST_STR;
			content->SpecificContentType = VISContentInfo::VIS_SpecificContentType::CONST_STR;
			return;
		}
		bool isNum = true;
		for (auto i = content->Content.begin(); i != content->Content.end(); i++) {
			if ((!(*i).isNumber()) && (*i) != ".") {
				isNum = false;
				break;
			}
		}
		if (isNum) {
			content->ContentType = VISContentInfo::VIS_ContentType::CONST_NUM;
			content->SpecificContentType = VISContentInfo::VIS_SpecificContentType::CONST_NUM;
			return;
		}
		content->ContentType = VISContentInfo::VIS_ContentType::WORD;
		content->SpecificContentType = VISContentInfo::VIS_SpecificContentType::WORD;
		return;
	}
	_Public void loadVISFile(QString fileFolder, QString fileName) {
		QFile file(fileFolder + "/" + fileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			throw std::exception(QString("can not open the file: " + file.fileName()).toStdString().c_str());
		}
		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line = in.readLine();
			LineContentData lineData = lineContentSplitter(line);
			if (!lineData.ContentDataList.empty()) {
				FileContent.append(lineData);
			}
		}

		ContentData Cend = { "END", VISContentInfo::VIS_ContentType::END, VISContentInfo::VIS_SpecificContentType::END };
		LineContentData end;
		end.Indentation = 0;
		end.ContentDataList.append(Cend);
		FileContent.append(end);
		for (auto i = FileContent.begin(); i != FileContent.end(); i++) {
			std::cout << (*i).Indentation<<"\t";
			for (auto j = (*i).ContentDataList.begin(); j != (*i).ContentDataList.end(); j++) {
				std::cout<<(*j).Content.toStdString()<<"\t";
			}
			std::cout << "\nCT\t";
			for (auto j = (*i).ContentDataList.begin(); j != (*i).ContentDataList.end(); j++) {
				std::cout << (int)(*j).ContentType << "\t";
			}
			std::cout << "\nST\t";
			for (auto j = (*i).ContentDataList.begin(); j != (*i).ContentDataList.end(); j++) {
				std::cout << (int)(*j).SpecificContentType << "\t";
			}
			std::cout << std::endl;
		}
	}
	_Public FileContentData getAnalyzedFileContent() {
		return FileContent;
	}
};
