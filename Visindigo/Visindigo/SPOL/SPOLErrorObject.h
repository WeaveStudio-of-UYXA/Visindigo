#pragma once
#include "SPOLVARObject.h"

class SPOLExec_ERROR :public SPOLExec_VAR {
	_Public ENUM ErrorType{
		DefinitionNotFound,
		TypeMismatch,
		NumberDividedByZero,
		ParameterMismatch,
		SyntaxParsingFailed,
		NullReference,
		NotApplicableOperator,
	};
	_Public def_init SPOLExec_ERROR(SPOLExecObject* parent = NULLOBJECT) :SPOLExec_VAR(parent) { ValueType = VARType::Error; }
	_Public def_init SPOLExec_ERROR(ErrorType type, SPOLExecObject* parent = NULLOBJECT) : SPOLExec_VAR(parent) { ValueType = VARType::Error; setValue(type); }
	_Public def_init SPOLExec_ERROR(SPOLExec_VAR* passObj, SPOLExecObject* parent = NULLOBJECT) : SPOLExec_VAR(parent) { ValueType = VARType::Error; markPass(passObj); }
	_Public def_init SPOLExec_ERROR(SPOLExec_VAR* passObj, ErrorType type, SPOLExecObject* parent = NULLOBJECT) : SPOLExec_VAR(parent) { ValueType = VARType::Error; setValue(type); markPass(passObj); }
	_Public void setValue(ErrorType type);
	_Public void markPass(SPOLExec_VAR* passObj);
};

//以下为重构后内容
class SPOLException {
	QString what();
};
class SPOLRuntimeException{

};