#include "SPOLFUNCObject.h"

SPOLExecObject* SPOLExec_FUNC::call(SPOLExecObject* parentEnv, SPOLExecObject* para) {
	if (ParaList.length() != para->getChildren().length()) {
		return new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::ParameterMismatch);
	}
	else {
		QVector<SPOLExecObject*> paraList = para->getChildren();
		for (int i = 0; i <paraList.length(); i++) {
			paraList[i]->setParent(this);
			paraList[i]->setName(ParaList[i]->getName());
		}
		SPOLExecObject* rtn = NULLOBJECT;
		for (auto i = NodeList.begin(); i != NodeList.end(); i++) {
			SPOLSyntaxType type = i->getSyntaxType();
			switch (type) {
			case SPOLSyntaxType::RETURN:
				rtn = i->exec(parentEnv, para, this);
				break;
			case SPOLSyntaxType::BREAK:
				rtn =  new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::SyntaxParsingFailed);
				break;
			case SPOLSyntaxType::CONTINUE:
				rtn =  new SPOLExec_ERROR(this, SPOLExec_ERROR::ErrorType::SyntaxParsingFailed);
				break;
			default:
				i->exec(this);
				break;
			}
		}
		delete para;
		for (auto i = Child.begin(); i != Child.end();) {
			if (*i != NULLOBJECT) {
				delete (*i);
				i = Child.erase(i);
			}
			else {
				i++;
			}
		}
		return rtn;
	}
}
void SPOLExec_FUNC::addSyntaxNode(SPOLSyntax_Node* node) {
	NodeList.append(node);
}
SPOLExecObject* SPOLExec_FUNC_Print::exec(SPOLExecObject* para) {
	QVector<SPOLExecObject*> paraList = para->getChildren();
	for (auto i = paraList.begin(); i != paraList.end(); i++) {
		SPOLExec_VAR* var = static_cast<SPOLExec_VAR*>(*i);
		switch(var->ValueType) {
		case VARType::Int:
			qDebug() << getInt();
			break;
		case VARType::Float:
			qDebug() << getFloat();
			break;
		case VARType::String:
			qDebug() << getString();
			break;
		case VARType::Bool:
			qDebug() << getBool();
			break;
		default:
			break;
		}
	}
	return NULLOBJECT;
}