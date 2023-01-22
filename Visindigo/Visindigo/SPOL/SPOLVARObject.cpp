#include "SPOLVARObject.h"
#include "SPOLErrorObject.h"
def_del SPOLExec_VAR::~SPOLExec_VAR() {
	if (ValueType == VARType::String || ValueType == VARType::Error) { delete Value.String; }
}
bool SPOLExec_VAR::isTempVar() {
	return IsLiteralTempVar;
}
bool SPOLExec_VAR::isNone() {
	return ValueType == VARType::None;
}
bool SPOLExec_VAR::isError() {
	return ValueType == VARType::Error;
}
void SPOLExec_VAR::setAsTempVar() {
	IsLiteralTempVar = true;
}
void SPOLExec_VAR::setValue(double value) {
	if (ValueType == VARType::String) { delete Value.String; }
	Value.Float = value;
	ValueType = VARType::Float;
}
void SPOLExec_VAR::setValue(bool value) {
	if (ValueType == VARType::String) { delete Value.String; }
	Value.Bool = value;
	ValueType = VARType::Bool;
}
void SPOLExec_VAR::setValue(QString value) {
	if (ValueType == VARType::String) { delete Value.String; }
	Value.String = new QString(value);
	ValueType = VARType::String;
}
void SPOLExec_VAR::setValue(SPOLExec_VAR* value) {
	if (ValueType == VARType::String) { delete Value.String; }
	Value.Quote = value;
	ValueType = VARType::Quote;
}
long long SPOLExec_VAR::getInt() {
	return Value.Int;
}
double SPOLExec_VAR::getFloat () {
	return Value.Float;
}
QString SPOLExec_VAR::getString() {
	return *(Value.String);
}
bool SPOLExec_VAR::getBool() {
	return Value.Bool;
}
SPOLExecObject* SPOLExec_VAR::getQuote() {
	return Value.Quote;
}
SPOLExec_VAR::VARType SPOLExec_VAR::getType() {
	return ValueType;
}
SPOLExec_VAR* SPOLExec_VAR::add(SPOLExec_VAR* var) {
	return this;
}
SPOLExec_VAR* SPOLExec_VAR::equal(SPOLExec_VAR* var, bool combine = false) {
	if (var == this) { return new SPOLExec_VAR(true); }
	if (ValueType != var->ValueType) {
		if (var->IsLiteralTempVar || !combine) { delete var; }
		return new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::TypeMismatch);
	}
	else {
		SPOLExec_VAR* rtn = NULLOBJECT;
		switch (ValueType)
		{
		case VARType::None:
			rtn = new SPOLExec_VAR(true);
			break;
		case VARType::Float:
			rtn =  new SPOLExec_VAR(Value.Float == var->Value.Float);
			break;
		case VARType::String:
			rtn = new SPOLExec_VAR((* Value.String) == *(var->Value.String));
			break;
		case VARType::Quote:
			rtn = new SPOLExec_VAR(Value.Quote == var->Value.Quote);
			break;
		case VARType::Int:
			rtn = new SPOLExec_VAR(Value.Int == var->Value.Int);
			break;
		case VARType::Bool:
			rtn = new SPOLExec_VAR(Value.Bool == var->Value.Bool);
			break;
		default:
			rtn = new SPOLExec_VAR(false);
		}
		rtn->setAsTempVar();
		if (var->isTempVar() || !combine) { delete var; }
		return rtn;
	}
}
SPOLExec_VAR* SPOLExec_VAR::moreThan(SPOLExec_VAR* var, bool combine = false) {
	if (ValueType != var->ValueType) {
		if (var->isTempVar() || !combine) { delete var; }
		return new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::TypeMismatch);
	}
	else {
		SPOLExec_VAR* rtn = NULLOBJECT;
		switch (ValueType)
		{
		case VARType::Int:
			rtn = new SPOLExec_VAR(Value.Int > var->Value.Int);
			break;
		case VARType::Float:
			rtn = new SPOLExec_VAR(Value.Float > var->Value.Float);
			break;
		case VARType::String:
			rtn = new SPOLExec_VAR(Value.String->size() > var->Value.String->size());
			break;
		case VARType::Bool:
			rtn = new SPOLExec_VAR(Value.Bool > var->Value.Bool);
			break;
		case VARType::Quote:
			rtn = new SPOLExec_VAR(Value.Quote > var->Value.Quote);
			break;
		case VARType::None:
			rtn = new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::NotApplicableOperator);
			break;
		default:
			rtn = new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::NotApplicableOperator);
		}
		rtn->setAsTempVar();
		if (var->isTempVar() || !combine) { delete var; }
		return rtn;
	}
}
SPOLExec_VAR* SPOLExec_VAR::lessThan(SPOLExec_VAR* var, bool combine = false) {
	if (ValueType != var->ValueType) {
		if (var->IsLiteralTempVar || !combine) { delete var; }
		return new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::TypeMismatch);
	}
	else {
		SPOLExec_VAR* rtn = NULLOBJECT;
		switch (ValueType)
		{
		case VARType::Int:
			rtn = new SPOLExec_VAR(Value.Int < var->Value.Int);
			break;
		case VARType::Float:
			rtn = new SPOLExec_VAR(Value.Float < var->Value.Float);
			break;
		case VARType::String:
			rtn = new SPOLExec_VAR(Value.String->size() < var->Value.String->size());
			break;
		case VARType::Bool:
			rtn = new SPOLExec_VAR(Value.Bool < var->Value.Bool);
			break;
		case VARType::Quote:
			rtn = new SPOLExec_VAR(Value.Quote < var->Value.Quote);
			break;
		case VARType::None:
			rtn = new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::NotApplicableOperator);
			break;
		default:
			rtn = new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::NotApplicableOperator);
		}
		rtn->setAsTempVar();
		if (var->isTempVar() || !combine) { delete var; }
		return rtn;
	}
}
SPOLExec_VAR* SPOLExec_VAR::notLessThan(SPOLExec_VAR* var) {
	SPOLExec_VAR* rt1 = this->equal(var, COMBINE);
	SPOLExec_VAR* rt2 = this->moreThan(var, COMBINE);
	rt1->setValue(rt1->Value.Bool || rt2->Value.Bool);
	delete rt2;
	if (var->isTempVar()) { delete var; }
	rt1->setAsTempVar();
	return rt1;
}
SPOLExec_VAR* SPOLExec_VAR::notMoreThan(SPOLExec_VAR* var) {
	SPOLExec_VAR* rt1 = this->equal(var, COMBINE);
	SPOLExec_VAR* rt2 = this->lessThan(var, COMBINE);
	rt1->setValue(rt1->Value.Bool || rt2->Value.Bool);
	delete rt2;
	if (var->isTempVar()) { delete var; }
	rt1->setAsTempVar();
	return rt1;
}
SPOLExec_VAR* SPOLExec_VAR::assign(SPOLExec_VAR* var) {
	Value = var->Value;
	ValueType = var->ValueType;
	for (auto i = var->Child.begin(); i != var->Child.end(); i++) {
		SPOLExec_VAR* newVar = new SPOLExec_VAR();
		newVar->assign((SPOLExec_VAR*)(* i));
		newVar->setParent(this);
	}
	Type = var->Type;
	if (var->isTempVar()) { delete var; }
	return this;
}

void SPOLExec_LIST::setValue(SPOLExec_LIST* var) {
	for (auto i = var->Child.begin(); i != var->Child.end(); i++) {
		SPOLExec_VAR* newVar = new SPOLExec_VAR();
		newVar->assign((SPOLExec_VAR*)(*i));
		newVar->setParent(this);
	}
	if (var->isTempVar()) { delete var; }
}

SPOLExec_LIST* SPOLExec_LIST::add(SPOLExec_VAR* var) {
	SPOLExec_VAR* child = new SPOLExec_VAR();
	child->assign(var);
	child->setParent(this);
	if (var->isTempVar()) { delete var; }
	return this;
}
SPOLExec_LIST* SPOLExec_LIST::add(SPOLExec_LIST* var) {
	for (auto i = var->Child.begin(); i != var->Child.end(); i++) {
		SPOLExec_VAR* newVar = new SPOLExec_VAR();
		newVar->assign((SPOLExec_VAR*)(*i));
		newVar->setParent(this);
	}
	if (var->isTempVar()) { delete var; }
	return this;
}
SPOLExec_VAR* SPOLExec_LIST::remove(SPOLExec_VAR* obj) {
	for (auto i = Child.begin(); i != Child.end(); i++) {
		if (static_cast<SPOLExec_VAR*>(*i)->equal(obj, COMBINE)) {
			delete (*i);
			Child.erase(i);
			break;
		}
	}
	if (obj->isTempVar()) { delete obj; }
	return this;
}
SPOLExec_VAR* SPOLExec_LIST::remove(int index) {
	if (index < 0 || index >= Child.size()) { return new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::ParameterMismatch); }
	delete Child[index];
	Child.erase(Child.begin() + index);
	return this;
}
SPOLExec_VAR* SPOLExec_LIST::get(int index) {
	if (index < 0 || index >= Child.size()) { return new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::ParameterMismatch); }
	return static_cast<SPOLExec_VAR*>(Child[index]);
}