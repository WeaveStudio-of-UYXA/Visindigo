#include "../SPOLInterpreter.h"
#include "../SPDFScripts.h"
void VIECMA_SPOL::loadStory(QJSValue spolLinesRaw) {
	qDebug() << "VIECMA_SPOL::loadStory";
	QStringList spolLines = spolLinesRaw.toVariant().toStringList();
	Scripts->Interpreter->executeSPOL(spolLines);
}