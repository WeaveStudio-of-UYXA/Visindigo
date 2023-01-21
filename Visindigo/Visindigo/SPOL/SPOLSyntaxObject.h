#pragma once
#include "SPOLObject.h"
#include "SPOLVARObject.h"

enum class SPOLSyntaxType {
	VAR, DEF, CLASS,
	RETURN, BREAK, CONTINUE,
	//IF, ELSE, ELIF,
	//WHILE, FOR,
	NUMBER, STRING,
	CALL, DEFNAME,
	OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE,
	OP_EQUAL, OP_NOT_EQUAL, OP_GREATER, OP_LESS, OP_GREATER_EQUAL, OP_LESS_EQUAL,
	OP_AND, OP_OR, OP_NOT,
	OP_ASSIGN,
	SYNERROR
};

class SPOLSyntax_Node :public SPOLExecObject
{
	_Public def_init SPOLSyntax_Node(SPOLExecObject* parent);
	_Public SPOLSyntaxType Type;
	_Public bool TopNode;
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

