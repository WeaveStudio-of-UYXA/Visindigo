#pragma once
#include "SPOLSyntaxObject.h"

class SPOLExec_FUNC :public SPOLExec_VAR {
	_Public QVector<SPOLSyntax_Node> NodeList;
	_Public QVector<SPOLExec_VAR*> ParaList;
	_Public def_init SPOLExec_FUNC(QString FuncName, SPOLExecObject* parent = NULLOBJECT) :SPOLExec_VAR(parent) { Name = FuncName; Type = ExecType::Func; setParent(parent); };
	_Public SPOLExecObject* call(SPOLExecObject* parentEnv, SPOLExecObject* parList);
	_Public void addSyntaxNode(SPOLSyntax_Node*);
	_Public void setParaList(QVector<SPOLExec_VAR*> paraListSet);
};

class SPOLExec_FUNC_Print :public SPOLExec_FUNC {
	_Public def_init SPOLExec_FUNC_Print(SPOLExecObject* parent = NULLOBJECT) :SPOLExec_FUNC("print", parent) { Type = ExecType::Func; };
	_Public SPOLExecObject* exec(SPOLExecObject*);
};