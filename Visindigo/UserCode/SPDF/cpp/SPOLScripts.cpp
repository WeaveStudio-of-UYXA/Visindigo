#include "../SPOLInterpreter.h"
#include "../SPDFScripts.h"
void VIECMA_SPOL::loadStory(QJSValue spolLinesRaw) {
	qDebug() << "VIECMA_SPOL::loadStory";
	QStringList spolLines = spolLinesRaw.toVariant().toStringList();
	Scripts->Interpreter->executeSPOL(spolLines);
}

void VIECMA_SPOL::installParser(QJSValue parser) {
	SPDFVIESParserContainer* parserContainer = new SPDFVIESParserContainer(parser);
	Scripts->Interpreter->addParser(parserContainer);
}