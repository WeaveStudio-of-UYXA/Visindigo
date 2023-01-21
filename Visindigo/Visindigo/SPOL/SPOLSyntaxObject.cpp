#include "SPOLSyntaxObject.h"

def_init SPOLSyntax_Node::SPOLSyntax_Node(SPOLExecObject* parent):SPOLExecObject(SPOLExecObject::ExecType::Logic, parent) {
	this->TopNode = false;
	this->Type = SPOLSyntaxType::SYNERROR;
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
	static_cast<SPOLExec_VAR*>(returnObj)->copyFrom(target);
	return returnObj;
}