#include "SPOLSyntax.h"

SPOLExecObject SPOLSyntax::exec(QString code) {
	SPOLExecObject obj(SPOLExecObject::ExecType::Var);
	QStringList LINE = code.split("\n");
	auto i = LINE.begin();
	execALine(i);
	return SPOLExecObject(SPOLExecObject::ExecType::Var);
}
SPOLExecObject SPOLSyntax::execALine(QStringList::Iterator i) {
	return SPOLExecObject(SPOLExecObject::ExecType::Var);
}
SPOLExecObject SPOLSyntax::execACell(QStringList::Iterator cell) {
	QString cellStr = *cell;
	return SPOLExecObject(SPOLExecObject::ExecType::Var);
}
SPOLSyntaxType SPOLSyntax::wordAnalyzer(QString code, SPOLSyntaxType frontType, SPOLExecObject* parentEnv, SPOLExecObject** returnObj) {
	if (frontType == SPOLSyntaxType::VAR) {
		if (parentEnv->hasChild(code, returnObj)) {
			return SPOLSyntaxType::SYNERROR;
		}
		else {
			SPOLExecObject* obj = new SPOLExec_VAR();
			obj->setName(code);
			*returnObj = obj;
			return SPOLSyntaxType::DEFNAME;
		}
	}
	else if (frontType == SPOLSyntaxType::DEF) {
		if (parentEnv->hasChild(code, returnObj)) {
			return SPOLSyntaxType::SYNERROR;
		}
		else {
			SPOLExecObject* obj = new SPOLExec_FUNC();
			obj->setName(code);
			*returnObj = obj;
			return SPOLSyntaxType::DEFNAME;
		}
	}
	else if (frontType == SPOLSyntaxType::CLASS) {
		if (parentEnv->hasChild(code, returnObj)) {
			return SPOLSyntaxType::SYNERROR;
		}
		else {
			SPOLExecObject* obj = new SPOLExec_VAR();
			obj->setName(code);
			*returnObj = obj;
			return SPOLSyntaxType::DEFNAME;
		}
	}
	
	if (code == "var") {
		return SPOLSyntaxType::VAR;
	}
	else if (code == "def") {
		return SPOLSyntaxType::DEF;
	}
	else if (code == "class") {
		return SPOLSyntaxType::CLASS;
	}
	else if (code == "if") {
		//return SPOLSyntaxType::IF;
	}
	else if (code == "else") {
		//return SPOLSyntaxType::ELSE;
	}
	else if (code == "elif") {
		//return SPOLSyntaxType::ELIF;
	}
	else if (code == "while") {
		//return SPOLSyntaxType::WHILE;
	}
	else if (code == "for") {
		//return SPOLSyntaxType::FOR;
	}
	//匹配所有整数和小数
	else if (QRegExp("[0-9]+[.][0-9]+").exactMatch(code)) {
		SPOLExec_VAR* var = new SPOLExec_VAR();
		var->setValue(code.toDouble());
		*returnObj = var;
		return SPOLSyntaxType::NUMBER;
	}
	else if (code.startsWith("\"") && code.endsWith("\"")) {
		SPOLExec_VAR* var = new SPOLExec_VAR();
		var->setValue(code.section("\"", 1, -2));
		*returnObj = var;
		return SPOLSyntaxType::STRING;
	}
	else if (code.split(".")[0] == "this") {
		if (parentEnv->Parent->hasChild(code.section(".", 1, -1), returnObj)) {
			return SPOLSyntaxType::DEFNAME;
		}
		else {
			return SPOLSyntaxType::SYNERROR;
		}
	}
	else if (ObjectPool->hasDefObject(code, returnObj)) {
		return SPOLSyntaxType::DEFNAME;
	}
	else if (parentEnv->hasChild(code, returnObj)) {
		return SPOLSyntaxType::DEFNAME;
	}
	else {
		return SPOLSyntaxType::SYNERROR;
	}
}
void SPOLSyntax::escapeCharacterRestore(QString* code) {
	//转义字符还原
	code->replace("\\n", "\n");
	code->replace("\\t", "\t");
	code->replace("\\r", "\r");
}
QStringList SPOLSyntax::wordSplitter(QString code) {
	QStringList wordList;
	QString word = "";
	bool inString = false;
	auto b = code.begin();           //be care of this ↓ 
	for (auto i = code.begin(); i != code.end(); b = i++) {
		if ((*i == '"' && *b != '\\') || (*i == '\'' && *b != '\\')) {
			if (!inString) {
				if (word != "") { wordList.append(word); }
				word = *i;
			}
			else {
				word.append(*i);
				wordList.append(word);
				word = "";
			}
			inString = !inString;
			continue;
		}
		if (!inString) {
			if ((*i == ' ' || *i == '\t' || *i == '\r' || *i == '\t')) {
				if (word != "") { wordList.append(word); }
				word = "";
				continue;
			}
			else if (*i == '+' || *i == '-' || *i == '*' || *i == '/' || *i == ':' || *i == '!' || *i == ",") {
				if (word != "") { wordList.append(word); }
				wordList.append(*i);
				word = "";
				continue;
			}
			else if (*i == '>' || *i == "<") {
				if (*b == '=') {
					wordList.last() += *i;
				}
				else {
					if (word != "") { wordList.append(word); }
					wordList.append(*i);
				}
				word = "";
				continue;
			}
			else if (*i == '=') {
				if (*b == '+' || *b == '-' || *b == '*' || *b == '/' || *b == '=' || *b == '!') {
					wordList.last() += *i;
				}
				else {
					if (word != "") { wordList.append(word); }
					wordList.append(*i);
				}
				word = "";
				continue;
			}
		}
		word.append(*i);
	}
	if (word != "") { wordList.append(word); }
	return wordList;
}
void SPOLSyntax::removeInlineComments(QString* code) {
	//去除行内注释
	int commentStart = code->lastIndexOf("#");
	if (commentStart != -1) {
		code->remove(commentStart, code->length() - commentStart);
	}
}
QStringList SPOLSyntax::wordSplitterCompleted(QString code) {
	removeInlineComments(&code);
	escapeCharacterRestore(&code);
	return wordSplitter(code);
}
SPOLExecObject SPOLSyntax::lineAnalyzer(QString code, SPOLExecObject* parentEnv) {
	return SPOLExecObject(SPOLExecObject::ExecType::Var);
}