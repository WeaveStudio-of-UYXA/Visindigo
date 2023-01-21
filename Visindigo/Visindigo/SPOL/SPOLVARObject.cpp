#include "SPOLVARObject.h"

void SPOLExec_VAR::setValue(double value) {
	Value = QString::number(value);
	ValueType = VARType::Number;
}
void SPOLExec_VAR::setValue(QString value) {
	Value = value;
	ValueType = VARType::String;
}
void SPOLExec_VAR::setValue(SPOLExec_VAR* value) {
	Quote = value;
	ValueType = VARType::Quote;
}

double SPOLExec_VAR::getNumber() {
	return Value.toDouble();
}
QString SPOLExec_VAR::getString() {
	return Value;
}
SPOLExecObject* SPOLExec_VAR::getQuote() {
	return Quote;
}
SPOLExec_VAR::VARType SPOLExec_VAR::getType() {
	return ValueType;
}
bool SPOLExec_VAR::is(SPOLExec_VAR* var) {
	if (var == this) { return true; }
	if (ValueType != var->ValueType) {
		return false;
	}
	else {
		if (ValueType == VARType::Quote) {
			return Quote == var->Quote;
		}
		else {
			return Value == var->Value;
		}
	}
}
bool SPOLExec_VAR::moreThan(SPOLExec_VAR* var) {
	if (this->is(var)) { return false; }
	else {
		switch (ValueType)
		{
		case VARType::Number:
			return Value.toDouble() > var->Value.toDouble();
		case VARType::String:
			return Value.size() > var->Value.size();
		case VARType::Quote:
			return Quote > var->Quote;
		case VARType::Other:
			return Value.size() > var->Value.size();
		default:
			return false;
		}
	}
}
bool SPOLExec_VAR::lessThan(SPOLExec_VAR* var) {
	if (this->is(var)) { return false; }
	else {
		switch (ValueType)
		{
		case VARType::Number:
			return Value.toDouble() < var->Value.toDouble();
		case VARType::String:
			return Value.size() < var->Value.size();
		case VARType::Quote:
			return Quote < var->Quote;
		case VARType::Other:
			return Value.size() < var->Value.size();
		default:
			return false;
		}
	}
}
bool SPOLExec_VAR::notLessThan(SPOLExec_VAR* var) {
	return this->is(var) || this->moreThan(var);
}
bool SPOLExec_VAR::notMoreThan(SPOLExec_VAR* var) {
	return this->is(var) || this->lessThan(var);
}
void SPOLExec_VAR::copyFrom(SPOLExec_VAR* var) {
	Value = var->Value;
	ValueType = var->ValueType;
	for (auto i = var->Child.begin(); i != var->Child.end(); i++) {
		SPOLExec_VAR* newVar = new SPOLExec_VAR();
		newVar->copyFrom((SPOLExec_VAR*)(* i));
		newVar->setParent(this);
	}
	Type = var->Type;
}

void SPOLExec_CLASS::initTHIS() {
	SPOLExec_VAR* thisVar = new SPOLExec_VAR();
	thisVar->setName("this");
	thisVar->setValue("this");
	thisVar->setParent(this);
	Child.append(thisVar);
}