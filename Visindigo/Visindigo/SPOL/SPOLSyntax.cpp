#include "SPOLSyntax.h"

QString SPOLSyntax::load(QString path) {
	QFile file;
	qDebug() << path;
	if (!path.endsWith(".spol")) {
		file.setFileName(path + ".spol");
	}
	else {
		file.setFileName(path);
	}
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return { "\n" };
	}
	QTextStream in(&file);
	QStringList Code = in.readAll().replace(";","\n").split("\n");
	file.close();
	for (auto i = Code.begin(); i != Code.end();) {
		if ((* i).startsWith("import ")){
			QString fileName = (*i).split(" ")[1];
			(*i) = load(path.section("/",0,-2) + "/" + fileName.replace(".", "/"));
		}
		else if ((*i).isEmpty()) {
			i = Code.erase(i);
			continue;
		}
		i++;
	}
	return Code.join("\n");
}
QStringList SPOLSyntax::loadCompleted(QString path) {
	QStringList codeList = SPOLSyntax::load(path).split("\n");
	//下面这个部分是将一切行末换行符合并到上一行并且扬了空白行
	for (auto i = codeList.begin(); i != codeList.end();) {
		if ((*i).isEmpty()) {
			i = codeList.erase(i);
			continue;
		}
		if ((*i).endsWith("\\")) {
			auto j = i;
			*i = (*i).section("\\", 0, -2) + (*++j);
			codeList.erase(j);
			continue;
		}
		i++;
	}
	return codeList;
}

void SPOLSyntax::codeAnalyzer(QStringList* code, SPOLObjectPool* defPool) {
	for (auto i = code->begin(); i != code->end();) {
		QStringList lineInfo = SPOLSyntax::wordSplitterCompleted(*i);
		if (lineInfo[0] == "def") {
			i++;
			SPOLExec_FUNC* funcDef = new SPOLExec_FUNC(lineInfo[1]);
			SPOLSyntax::partAnalyzer(SPOLSyntax::getIndentValue(&(*i)), code, &i, funcDef);
			defPool->addDefObject(funcDef);
			continue;//注意，由partAnalyzer嵌套调用的那个codeAnalyzer完成最后一个++
		}
	}
}
void SPOLSyntax::partAnalyzer(int IndentValue, QStringList* code, QStringList::iterator* i, SPOLExecObject* parentDef) {
	for (*i; *i != code->end();(*i)++) {
		if (SPOLSyntax::getIndentValue(&(**i)) != IndentValue) { return; }
		else {
			QStringList lineInfo = SPOLSyntax::wordSplitterCompleted(**i);
			if (lineInfo[0] == "def") {
				i++;
				SPOLExec_FUNC* funcDef = new SPOLExec_FUNC(lineInfo[1]);
				SPOLSyntax::partAnalyzer(SPOLSyntax::getIndentValue(&(**i)), code, i, funcDef);
				funcDef->setParent(parentDef);
				continue;//注意，由partAnalyzer嵌套调用的那个codeAnalyzer完成最后一个++
			}
			else {
				static_cast<SPOLExec_FUNC*>(parentDef)->addSyntaxNode(SPOLSyntax::lineAnalyzer(&lineInfo));
			}
		}
	}
}
int SPOLSyntax::getIndentValue(QString* code) {
	int indent = 0;
	for (auto i = code->begin(); i != code->end(); i++) {
		if (*i == '\t') {
			indent += 4;
		}
		else if (*i == ' ') {
			indent += 0;
		}
		else {
			break;
		}
	}
	return indent;
}
SPOLSyntax_Node* SPOLSyntax::lineAnalyzer(QStringList* Code) {
	return NULLOBJECT;
}
SPOLSyntax_Node* SPOLSyntax::wordAnalyzer(QStringList codeList, SPOLSyntax_Node* node) {
	return NULLOBJECT;
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
			//SPOLExecObject* obj = new SPOLExec_FUNC();
			//obj->setName(code);
			//*returnObj = obj;
			//return SPOLSyntaxType::DEFNAME;
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
	//else if (ObjectPool->hasDefObject(code, returnObj)) {
		//return SPOLSyntaxType::DEFNAME;
	//}
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
	int BracketDepth = 0;
	auto b = code.begin();           //be care of this ↓ 
	QList<QChar> BracketStart = { '(', '{', '[' };
	QList<QChar> BracketEnd = { ')', '}', ']' };
	QChar BracketStartNow = '(';
	QChar BracketEndNow = ')';
	QString FREETest = code.simplified();
	if (FREETest.startsWith("|")) {
		wordList.append("|");
		wordList.append(FREETest.remove(0, 1));
		return wordList;
	}
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
			if (BracketStart.contains(*i)) {
				if (BracketDepth == 0) {
					BracketStartNow = *i;
					BracketEndNow = BracketEnd[BracketStart.indexOf(*i)];
					BracketDepth++;
					if (word != ""){wordList.append(word);}
					word = *i;
					continue;
				}
			}
			if (*i == BracketStartNow) {
				BracketDepth++;
				if (BracketDepth == 1) {
					if (word != "") { wordList.append(word); }
					word = *i;
					continue;
				}
			}
			else if (*i == BracketEndNow) {
				BracketDepth--;
				if (BracketDepth == 0) {
					word += *i;
					if (word != "") { wordList.append(word); }
					word = "";
					continue;
				}
			}
			if (BracketDepth == 0) {
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
	QStringList list = wordSplitter(code);
	for (auto i = list.begin(); i != list.end(); i++) {
		escapeCharacterRestore(&(* i));
	}
	return list;
}
