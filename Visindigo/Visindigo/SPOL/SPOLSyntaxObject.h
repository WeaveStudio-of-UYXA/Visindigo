#pragma once
#include "SPOLVARObject.h"
#include "SPOLErrorObject.h"
#include "SPOLObjectPool.h"
enum class SPOLSyntaxType {
	LINESTART,
	VAR, DEF, CLASS,
	RETURN, BREAK, CONTINUE,
	IF, ELSE, ELIF,
	WHILE, FOR,
	NUMBER, STRING,
	CALL, VARNAME,
	MARK_FREE,
	OP_ASSIGN,
	SYNERROR
};
class SPOLSyntax_Node
{
	_Public SPOLSyntaxType NodeType;
	_Public SPOLSyntax_Node* Top = NULLOBJECT; 
	_Public SPOLSyntax_Node* Left = NULLOBJECT;
	_Public SPOLSyntax_Node* Right = NULLOBJECT;
	_Public def_init SPOLSyntax_Node(SPOLSyntax_Node* parent);
	_Public def_del ~SPOLSyntax_Node();
	_Public bool isTopNode();
	_Public void setNodeType(SPOLSyntaxType type);
	_Public void setLeftType(SPOLSyntaxType type);
	_Public void setRightType(SPOLSyntaxType type);
	_Public void setLeft(SPOLSyntax_Node* left);
	_Public void setRight(SPOLSyntax_Node* right);
	_Public SPOLSyntaxType getSyntaxType();
	_Public virtual SPOLExecObject* exec(SPOLExecObject* parentEnv, SPOLExecObject* paraList, SPOLObjectPool* defPool) { return NULLOBJECT; };
};
class SPOLSyntax_CALL :public SPOLSyntax_Node {
	_Public def_init SPOLSyntax_CALL(SPOLSyntax_Node* parent);
	_Public QString callName;
	_Public SPOLExecObject* exec(SPOLExecObject* parentEnv, SPOLExecObject* paraList, SPOLObjectPool* defPool) override;
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

