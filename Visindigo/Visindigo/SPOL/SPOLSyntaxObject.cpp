#include "SPOLSyntaxObject.h"

def_init SPOLSyntax_Node::SPOLSyntax_Node(SPOLExecObject* parent = NULLOBJECT):SPOLExecObject(SPOLExecObject::ExecType::Logic, parent) {
	if (parent = NULLOBJECT) { this->TopNode = false; }
	else { 
		this->setParent(parent); 
		this->TopNode = true;
	}
	this->Type = SPOLSyntaxType::SYNERROR;
}
void SPOLSyntax_Node::setAsTopNode() {
	this->TopNode = true;
}
bool SPOLSyntax_Node::isTopNode() {
	return TopNode;
}
void SPOLSyntax_Node::setSyntaxType(SPOLSyntaxType type) {
	this->Type = type;
}
SPOLSyntaxType SPOLSyntax_Node::getSyntaxType(void) {
	return Type;
}
def_init SPOLSyntax_VAR::SPOLSyntax_VAR(bool isTopNode, SPOLExecObject* parent):SPOLSyntax_Node(parent) {
	this->TopNode = isTopNode;
	this->Type = SPOLSyntaxType::VAR;
}

SPOLExecObject* SPOLSyntax_VAR::exec(SPOLExecObject* parentEnv) {
	SPOLExecObject* returnObj = new SPOLExec_VAR();
	returnObj->setName(this->getName());
	returnObj->setParent(parentEnv);
	return returnObj;
}

def_init SPOLSyntax_OP_ASSIGN::SPOLSyntax_OP_ASSIGN(bool isTopNode, SPOLExecObject* parent):SPOLSyntax_Node(parent) {
	this->TopNode = isTopNode;
	this->Type = SPOLSyntaxType::OP_ASSIGN;
}

SPOLExecObject* SPOLSyntax_OP_ASSIGN::exec(SPOLExecObject* parentEnv) {
	SPOLExecObject* returnObj = NULLOBJECT;
	parentEnv->hasChild(this->getName(), &returnObj) ? returnObj : NULLOBJECT;
	SPOLExec_VAR* target = static_cast<SPOLExec_VAR*>(this->getChildren()[0]);
	static_cast<SPOLExec_VAR*>(returnObj)->assign(target);
	return returnObj;
}