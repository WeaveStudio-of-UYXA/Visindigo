#include "SPOLSyntax.h"

SPOLExecObject SPOLSyntax::exec(QString code) {
	SPOLExecObject obj(SPOLExecObject::ExecType::Var);
	QStringList LINE = code.split("\n");
	auto i = LINE.begin();
	execALine(i);
}
SPOLExecObject SPOLSyntax::execALine(QStringList::Iterator i) {
	
}