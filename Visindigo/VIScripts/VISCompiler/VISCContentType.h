#pragma once
#include <QtCore>
class VISContentInfo {
public:
	static QStringList Keyword_Addname;
	static QStringList Keyword_TFN;
	static QStringList Keyword_MemBranCycExcSwi;
	static QStringList Keyword_Access;
	static QStringList Keyword_Polymorphic;
	static QStringList Keyword_FuncBase;
	static QStringList Keyword_Logic;
	static QStringList Keyword_PreComp;
	static QStringList Keyword_Note;
	static QStringList KeywordForbidden;
	static QStringList SymbolForbidden;
	enum class VIS_ContentType {
		KEYWORD = 100,
		WORD = 400,
		CONST_NUM = 410,
		CONST_STR = 411,
		SYMBOL = 500,
		UNKNOWN = 999,
		END = 990,
	};
	enum class VIS_SpecificContentType {
		KEYWORD = 100,
		INCLUDE = 10,
		//Keyword
		VAR = 300, DEF = 301, CLASS = 302,
		_TRUE = 310, _FALSE = 311, _None = 312,
		NEW = 320, DEL = 321,
		STATIC = 330,

		IF = 110, ELIF = 111, ELSE = 212,
		WHILE = 113, FOR = 114, CONTINUE = 215, BREAK = 216,

		CATCH = 120, THROW = 121, TRY = 222,
		SWITCH = 123, CASE = 224,

		PUBLIC = 230, PRIVATE = 231, PROTECTED = 232,

		FINAL = 240, ABSTRACT = 241, OVERRIDE = 242, VIRTUAL = 243,

		RETURN = 250, _THIS = 251, SUPER = 252,

		NOT = 260, AND = 261, OR = 262, IS = 263, _IN = 264, AS = 265,

		DEPRECATED = 270, OBSOLETE = 271,

		//Word
		WORD = 400,

		CONST_NUM = 410, CONST_STR = 411,

		//Keyword forbidden
		WITH = 420,  FROM = 422,
		_VOID = 423, _CONST = 424,
		INLINE = 425, 
		_EVENT = 435, CALL = 436,
		AUTO = 437, TEMPLATE = 438, TYPENAME = 439, FRIEND = 440,
		_ENUM = 441, UNION = 442, STRUCT = 443, NAMESPACE = 444,
		GOTO = 445,
		USING = 446, TYPEDEF = 447,
		EXTERN = 448, 
		EXPORT = 449, IMPORT = 450,

		//Symbol
		SYMBOL = 500,

		ADD = 510, SUB = 511, MUL = 512, DIV = 513, MOD = 514,
		MORE = 520, LESS = 521, EQUAL = 522, NOTEQ = 523, NOTLE = 524, NOTMO = 525,
		ASSIGN = 530, COMMA = 531, 
		
		COLON = 532, ARROW = 533, 

		IMAO = 550, IMSO = 551, POWER = 552, RADICAL = 553,
		IMADD = 560, IMSUB = 561, IMMUL = 562, IMDIV = 563,
		LPAR = 570, RPAR = 571, LBKT = 572, RBKT = 573, LBRC = 574, RBRC = 575,
		AT = 580,

		//Symbol forbidden
		SIF = 700,
		XAND = 701, XOR = 702,
		SHARP = 703,
		SEMI = 704,
		PESO = 705,

		END = 990,
		//Unknown
		UNKNOWN = 999
	};

	struct ContentData {
		QString Content;
		VIS_ContentType ContentType;
		VIS_SpecificContentType SpecificContentType;
	};
	struct LineContentData {
		int Indentation;
		QList<ContentData> ContentDataList;
	};
};
typedef VISContentInfo::ContentData ContentData;
typedef VISContentInfo::LineContentData LineContentData;
typedef QList<LineContentData> FileContentData;


