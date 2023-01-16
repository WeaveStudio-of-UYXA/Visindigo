#include "SPOLObject.h"
void SPOLExecObject::setParent(SPOLExecObject* parent) {
	if (parent != Q_NULLPTR) {
		this->Parent = parent;
		parent->addChild(this);
	}
}
void SPOLExecObject::addChild(SPOLExecObject* child) {
	this->Child.append(child);
}
void SPOLExecObject::removeChild(SPOLExecObject* child) {
	this->Child.removeOne(child);
}
SPOLExecObject::~SPOLExecObject() {
	if (Parent != Q_NULLPTR) {
		this->Parent->removeChild(this);
	}
	while (Child.size() != 0) {
		auto i = Child.begin();
		if (*i != Q_NULLPTR) { delete (*i); }
	}
}
SPOLExecObject* SPOLExecObject::getParent() {
	return (SPOLExecObject*)this->parent();
}
QList<SPOLExecObject*> SPOLExecObject::getChildren() {
	return this->Child;
}
bool SPOLExecObject::hasChild(QString fullName, SPOLExecObject** returnObj) {
	QStringList name = fullName.split(".");
	SPOLExecObject* rtn = Q_NULLPTR;
	auto n = name.begin();
	for (auto i = Child.begin(); i != Child.end(); i++) {
		if ((*i)->Name == *n) { 
			if (n != name.end()) {
				n++;
				return (*i)->hasChild(&name, &n, &rtn);
			}
			else { 
				rtn = (*i);
				*returnObj = rtn;
				return true; 
			}
		}
	}
	return false;
}
bool SPOLExecObject::hasChild(QStringList* nameList, QStringList::Iterator* name, SPOLExecObject** returnObj) {
	for (auto i = Child.begin(); i != Child.end(); i++) {
		if ((*i)->Name == **name) {
			if (*name != nameList->end()) {
				*name++;
				return (*i)->hasChild(nameList, name, returnObj);
			}
			else {
				*returnObj = (*i);
				return true;
			}
		}
	}
	return false;
}
void SPOLExec_VAR::setValue(double value, int index) {
	if (index != 0) { IsList = true; }
	Value[index] = QString::number(value);
	ValueType[index] = VARType::Number;
}
void SPOLExec_VAR::setValue(QString value, int index) {
	if (index != 0) { IsList = true; } 
	Value[index] = value;
	ValueType[index] = VARType::String;
}
void SPOLExec_VAR::setValue(QStringList value, SPOLVarTypeList type) {
	if (value.size() != type.size()) {
		return;
	}
	else {
		Value = value;
		ValueType = type;
	}
}
double SPOLExec_VAR::getNumber(int index) {
	return Value[index].toDouble();
}
QString SPOLExec_VAR::getString(int index) {
	return Value[index];
}
QStringList SPOLExec_VAR::getOther() {
	return Value;
}
SPOLExec_VAR::VARType SPOLExec_VAR::getType(int index) {
	return ValueType[index];
}
SPOLVarTypeList SPOLExec_VAR::getTypeList() {
	return ValueType;
}
bool SPOLExec_VAR::is(SPOLExec_VAR* var) {
	if (var == this) { return true; }
	else {
		if (IsList) {
			if (Value.size() == var->Value.size()) {
				for (int i = 0; i < Value.length(); i++) {
					if (Value[i] == var->Value[i] && ValueType[i] == var->ValueType[i]) { continue; }
					else { return false; }
				}
				return true;
			}
			else { return false; }
		}
		else {
			return Value[0] == var->Value[0] && ValueType[0] == var->ValueType[0];
		}
	}
}
bool SPOLExec_VAR::moreThan(SPOLExec_VAR* var) {
	if (this->is(var)) { return false; }
	else {
		if (IsList) {
			return var->Value.size() > Value.size();
		}
		else {
			switch (ValueType[0])
			{
			case VARType::Number:
				return Value[0].toDouble() > var->Value[0].toDouble();
			case VARType::String:
				return Value[0].size() > var->Value[0].size();
			case VARType::Other:
				return Value[0].size() > var->Value[0].size();
			default:
				return false;
			}
		}
	}
}
bool SPOLExec_VAR::lessThan(SPOLExec_VAR* var) {
	if (this->is(var)) { return false; }
	else {
		if (IsList) {
			return var->Value.size() < Value.size();
		}
		else {
			switch (ValueType[0])
			{
			case VARType::Number:
				return Value[0].toDouble() < var->Value[0].toDouble();
			case VARType::String:
				return Value[0].size() < var->Value[0].size();
			case VARType::Other:
				return Value[0].size() < var->Value[0].size();
			default:
				return false;
			}
		}
	}
}
bool SPOLExec_VAR::notLessThan(SPOLExec_VAR* var) {
	return this->is(var) || this->moreThan(var);
}
bool SPOLExec_VAR::notMoreThan(SPOLExec_VAR* var) {
	return this->is(var) || this->lessThan(var);
}
bool SPOLExec_VAR::copyFrom(SPOLExec_VAR* var) {
	Value = var->Value;
	ValueType = var->ValueType;
	IsList = var->IsList;
}