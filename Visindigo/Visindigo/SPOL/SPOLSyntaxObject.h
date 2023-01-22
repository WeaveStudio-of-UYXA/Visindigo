#pragma once
#include "SPOLVARObject.h"
#include "SPOLErrorObject.h"

enum class SPOLSyntaxType {
	LINESTART,
	VAR, DEF, CLASS,
	RETURN, BREAK, CONTINUE,
	IF, ELSE, ELIF,
	WHILE, FOR,
	NUMBER, STRING,
	CALL, DEFNAME,
	OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE,
	OP_EQUAL, OP_NOT_EQUAL, OP_GREATER, OP_LESS, OP_GREATER_EQUAL, OP_LESS_EQUAL,
	OP_AND, OP_OR, OP_NOT,
	MARK_FREE,
	OP_ASSIGN,
	SYNERROR
};
enum class SPOLLineType {
	DEF,
	CLASS,
	NORMAL,
	IF,
	ELSE,
	ELIF,
	WHILE,
	FOR,
	RETURN,
	BREAK,
	CONTINUE,
	FREE,
	EMPTY
};
class SPOLSyntax_Node :public SPOLExecObject
{
	_Public def_init SPOLSyntax_Node(SPOLExecObject* parent);
	_Public SPOLSyntaxType Type;
	_Public bool TopNode;
	_Public void setAsTopNode();
	_Public bool isTopNode();
	_Public void setSyntaxType(SPOLSyntaxType type);
	_Public SPOLSyntaxType getSyntaxType();
};
class SPOLSyntax_DEF :public SPOLSyntax_Node{
	_Public def_init SPOLSyntax_DEF(bool isTopNode, SPOLExecObject* parent);
	
};
class SPOLSyntax_CALL :public SPOLSyntax_Node {
	_Public def_init SPOLSyntax_CALL(bool isTopNode, SPOLExecObject* parent);
	_Public SPOLExecObject* exec(SPOLExecObject*);
};
class SPOLSyntax_VAR :public SPOLSyntax_Node
{
	_Public def_init SPOLSyntax_VAR(bool isTopNode, SPOLExecObject* parent);
	_Public SPOLExecObject* exec(SPOLExecObject*);
};

class SPOLSyntax_OP_ASSIGN :public SPOLSyntax_Node
{
	_Public def_init SPOLSyntax_OP_ASSIGN(bool isTopNode, SPOLExecObject* parent);
	_Public SPOLExecObject* exec(SPOLExecObject*);
};

