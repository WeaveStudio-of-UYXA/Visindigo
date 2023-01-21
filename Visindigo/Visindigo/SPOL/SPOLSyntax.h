#pragma once
#include "SPOLObject.h"
#include "SPOLSyntaxObject.h"
#include "SPOLObjectPool.h"
#include "SPOLVARObject.h"

class SPOLSyntax {
	_Public SPOLObjectPool* ObjectPool;
	_Public SPOLExecObject exec(QString code);
	_Public SPOLExecObject execFile(QString path);
	_Private SPOLExecObject execALine(QStringList::iterator i);
	_Private SPOLExecObject execACell(QStringList::iterator cell);
	_Public static void escapeCharacterRestore(QString* code);
	_Public static QStringList wordSplitter(QString code);
	_Public static void removeInlineComments(QString* code);
	_Public static QStringList wordSplitterCompleted(QString code);
	_Private SPOLExecObject bracketSplitter(QString code);
	_Private SPOLSyntaxType wordAnalyzer(QString code, SPOLSyntaxType frontType, SPOLExecObject* parentEnv, SPOLExecObject** returnObj);
	_Private SPOLExecObject lineAnalyzer(QString code, SPOLExecObject* parentEnv);
	_Private SPOLExecObject arithmeticConstructor(QString code);
};