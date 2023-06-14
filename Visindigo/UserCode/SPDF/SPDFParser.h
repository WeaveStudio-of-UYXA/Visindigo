#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "SPDFChara.h"
#include "SPDFTerminal.h"
#include "SPDFWorkingEnv.h"

class SPOLInterpreter;
class SPDFAbstractControllerParser :public VIObject 
{
	Q_OBJECT;
	VI_OBJECT;
	friend class SPOLInterpreter;
	VI_ProtectedProperty(QString, ControllerName);
	_Protected SPDFParserObjectList Parameters;
	_Public QMap<QString, QString>* Context;
	_Public virtual bool parseLine(const QString& line) PureVirtual;
};


