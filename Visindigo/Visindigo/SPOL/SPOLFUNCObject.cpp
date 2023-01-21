#include "SPOLFUNCObject.h"

SPOLExecObject* SPOLExec_FUNC::exec(SPOLExecObject* para) {
	if (ParaList->getChildren().length() != para->getChildren().length()) {
		return NULLOBJECT;
	}
	else {
		QList<SPOLExecObject*> paraList = para->getChildren();
		QList<SPOLExecObject*> defParaList = ParaList->getChildren();
		for (int i = 0; i <paraList.length(); i++) {
			paraList[i]->setParent(ParaList);
			paraList[i]->setName(defParaList[i]->getName());
		}
		for (auto i = NodeList.begin(); i != NodeList.end(); ) {
			SPOLSyntaxType type = i->Type;
			switch (type) {
			case SPOLSyntaxType::RETURN:
				return i->exec(this);
				break;
			case SPOLSyntaxType::BREAK:
				return NULLOBJECT;
				break;
			case SPOLSyntaxType::CONTINUE:
				i = NodeList.begin();
				continue;
				break;
			default:
				i->exec(this);
				break;
			}
			i++;
		}
		return NULLOBJECT;
	}
}

SPOLExecObject* SPOLExec_FUNC_Print::exec(SPOLExecObject* para) {
	QList<SPOLExecObject*> paraList = para->getChildren();
	for (auto i = paraList.begin(); i != paraList.end(); i++) {
		SPOLExec_VAR* var = static_cast<SPOLExec_VAR*>(*i);
		if (var->IsList) { qDebug() << var->getOther(); }
		else { 
			switch (var->getType()) {
			case SPOLExec_VAR::VARType::Number:
				qDebug() << var->getNumber();
				break;
			case SPOLExec_VAR::VARType::String:
				qDebug() << var->getString();
				break;
			case SPOLExec_VAR::VARType::Other:
				qDebug() << var->getOther();
				break;
			} 
		}
	}
	return NULLOBJECT;
}