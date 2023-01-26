#include "SPOLSyntaxObject.h"
def_init SPOLSyntax_Node::SPOLSyntax_Node(SPOLSyntax_Node* parent = NULLOBJECT) {
	this->Top = parent;
}
def_del SPOLSyntax_Node::~SPOLSyntax_Node() {
	if (this->Left != NULLOBJECT) { delete this->Left; }
	if (this->Right != NULLOBJECT) { delete this->Right; }
}
bool SPOLSyntax_Node::isTopNode() {
	return this->Top == NULLOBJECT;
}
void SPOLSyntax_Node::setNodeType(SPOLSyntaxType type) {
	this->NodeType = type;
}
SPOLSyntaxType SPOLSyntax_Node::getSyntaxType() {
	return this->NodeType;
}
void SPOLSyntax_Node::setLeft(SPOLSyntax_Node* node) {
	if (this->Left != NULLOBJECT) { delete this->Left; }
	this->Left = node;
}
void SPOLSyntax_Node::setRight(SPOLSyntax_Node* node) {
	if (this->Right != NULLOBJECT) { delete this->Right; }
	this->Right = node;
}
def_init SPOLSyntax_CALL::SPOLSyntax_CALL(SPOLSyntax_Node* parent):SPOLSyntax_Node(parent) {
	this->setNodeType(SPOLSyntaxType::CALL);
}
SPOLExecObject* SPOLSyntax_CALL::exec(SPOLExecObject* parentEnv, SPOLExecObject* paraList, SPOLObjectPool* defPool) {
	SPOLExecObject* result = NULLOBJECT;
	defPool->hasDefObject(callName, &result);
	//SPOLExecObject* newobj = result->exec(NULLOBJECT, paraList);
	return NULLOBJECT;
}


