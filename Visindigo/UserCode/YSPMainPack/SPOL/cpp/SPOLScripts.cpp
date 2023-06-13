#include "../SPOLScripts.h"

void VIECMA_SPOL::loadStory(QStringList spolLines) {
	Scripts->Interpreter->executeSPOL(spolLines);
}