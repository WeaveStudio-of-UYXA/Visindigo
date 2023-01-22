#include "SPOLErrorObject.h"

void SPOLExec_ERROR::setValue(ErrorType type) {
	switch (type) {
	case ErrorType::DefinitionNotFound:
		this->Value.String = new QString("Definition not found");
		break;
	case ErrorType::TypeMismatch:
		this->Value.String = new QString("Type mismatch");
		break;
	case ErrorType::NumberDividedByZero:
		this->Value.String = new QString("Number divided by zero");
		break;
	case ErrorType::ParameterMismatch:
		this->Value.String = new QString("Parameter mismatch");
		break;
	case ErrorType::SyntaxParsingFailed:
		this->Value.String = new QString("Syntax parsing failed");
		break;
	case ErrorType::NullReference:
		this->Value.String = new QString("Null reference");
		break;
	case ErrorType::NotApplicableOperator:
		this->Value.String = new QString("Not applicable operator");
		break;
	default:
		this->Value.String = new QString("Unknown error");
	}
}

void SPOLExec_ERROR::markPass(SPOLExec_VAR* passObj) {
	SPOLExecObject* obj = new SPOLExecObject(ExecType::Var, this);
	obj->setName(passObj->getFullName());
}