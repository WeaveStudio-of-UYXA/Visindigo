#include "VISCContentType.h"
QStringList VISContentInfo::Keyword_Addname = {
	"var", "def", "function", "fn", "class", "static"
};
QStringList VISContentInfo::Keyword_TFN = {
	"true", "false", "null", "none",
	"True", "False", "Null", "None",
	"TRUE", "FALSE", "NULL", "NONE"
};
QStringList VISContentInfo::Keyword_MemBranCycExcSwi = {
	"new", "del", "delete",
	"if", "else", "elif",
	"while", "for", "continue", "break",
	"catch", "throw", "raise", "try",
	"switch", "case", "match"
};
QStringList VISContentInfo::Keyword_Access = {
	"public", "private", "protected", "friend"
};
QStringList VISContentInfo::Keyword_Polymorphic = {
	"final", "override", "virtual", "abstract"
};
QStringList VISContentInfo::Keyword_FuncBase = {
	"return", "this", "self", "super"
};
QStringList VISContentInfo::Keyword_Logic = {
	"and", "or", "not", "is", "in", "as"
};
QStringList VISContentInfo::Keyword_PreComp = {
	"include"
};
QStringList VISContentInfo::Keyword_Note = {
	"deprecated", "obsolete"
};
QStringList VISContentInfo::KeywordForbidden = {
	"with", "from", "void", "const",
	"inline",
	"event", "call", "auto", "template", "typename",
	"enum", "union", "struct", "namespace", "goto",
	"using", "typedef", "extern"
};

QStringList VISContentInfo::SymbolForbidden = {
	"?","&", "|", "#", ";", "$"
};