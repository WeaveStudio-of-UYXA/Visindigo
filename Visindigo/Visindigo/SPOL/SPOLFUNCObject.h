#pragma once
#include "SPOLVARObject.h"
#include "SPOLSyntaxObject.h"

class SPOLExec_FUNC :public SPOLExec_VAR {
	_Public QVector<SPOLSyntax_Node> NodeList;
	_Public SPOLExec_VAR* ParaList;
	_Public def_init SPOLExec_FUNC(SPOLExecObject* parent = NULLOBJECT) :SPOLExec_VAR(parent) { Type = ExecType::Func; };
	_Public SPOLExecObject* exec(SPOLExecObject*);
};

class SPOLExec_FUNC_Print :public SPOLExec_FUNC {
	_Public def_init SPOLExec_FUNC_Print(SPOLExecObject* parent = NULLOBJECT) :SPOLExec_FUNC(parent) { Name = "print"; Type = ExecType::Func; };
	_Public SPOLExecObject* exec(SPOLExecObject*);
};
};