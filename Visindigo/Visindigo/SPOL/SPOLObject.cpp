#include "SPOLObject.h"
void SPOLExecObject::setParent(SPOLExecObject* parent) {
	if (parent != NULLOBJECT) {
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
void SPOLExecObject::setName(QString name) {
	this->Name = name;
}
QString SPOLExecObject::getName() {
	return this->Name;
}
def_init SPOLExecObject::SPOLExecObject(ExecType type, SPOLExecObject* parent) { 
	setParent(parent); Type = type; 
}
def_del SPOLExecObject::~SPOLExecObject() {
	if (Parent != NULLOBJECT) {
		this->Parent->removeChild(this);
	}
	while (Child.size() != 0) {
		auto i = Child.begin();
		if (*i != NULLOBJECT) { delete (*i); }
	}
}
def_copy SPOLExecObject::SPOLExecObject(const SPOLExecObject& obj) {
	this->Name = obj.Name;
	this->Parent = obj.Parent;
	this->Child = obj.Child;
	this->Type = obj.Type;
}
SPOLExecObject* SPOLExecObject::getParent() {
	return Parent;
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
SPOLExecObject* SPOLExecObject::exec(SPOLExecObject* para) {
	return new SPOLExecObject(ExecType::Var);
}