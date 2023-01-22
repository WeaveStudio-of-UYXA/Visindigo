#pragma once
#include "SPOLSyntaxObject.h"
#include "SPOLFUNCObject.h"
#include "SPOLObjectPool.h"

class SPOLSyntax {
	_Public static QString load(QString path);
	_Public static void codeLineSpilter(QStringList* list, QString Code);
	_Public static void codeAnalyzer(QStringList* code, SPOLObjectPool* defPool);
	_Private static void codeAnalyzer(QStringList* code, QStringList::iterator i, SPOLObjectPool* defPool);
	_Public static SPOLExecObject* partAnalyzer(int IndentValue, QStringList* code, QStringList::iterator* i, SPOLObjectPool* defPool);
	_Public static int getIndentValue(QString* code);
	_Public static SPOLLineType lineAnalyzer(QString code, SPOLSyntax_Node* node);
	_Public static void escapeCharacterRestore(QString* code);
	_Public static QStringList wordSplitter(QString code);
	_Public static SPOLSyntax_Node* wordAnalyzer(QStringList codeList, SPOLSyntax_Node* node);
	_Public static void removeInlineComments(QString* code);
	_Public static QStringList wordSplitterCompleted(QString code);
	
	_Private SPOLExecObject* bracketSplitter(QString code);
	_Private SPOLSyntaxType wordAnalyzer(QString code, SPOLSyntaxType frontType, SPOLExecObject* parentEnv, SPOLExecObject** returnObj);
	_Private SPOLExecObject* arithmeticConstructor(QString code);
};
