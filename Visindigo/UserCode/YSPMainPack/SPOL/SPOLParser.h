#pragma once
#include "../../../Visindigo/VICore/VICore.h"
#include "SPOLChara.h"
#include "SPOLTerminal.h"
#include "SPOLWorkingEnv.h"
#define CREATE_SPOLControllerNewFunction(name) \
	_Protected  SPOL::name* new##name() { \
		SPOL::name* c = new SPOL::name(); \
		Types.push_back(SPOL::ControllerType::name); \
		Parameters.push_back(c); \
		return c; \
	}

class SPOLInterpreter;
class SPOLAbstractControllerParser :public VIObject 
{
	Q_OBJECT;
	VI_OBJECT;
	friend class SPOLInterpreter;
	VI_PrivateProperty(QString, ControllerName);
	_Private SPOL::ControllerTypeList Types;
	_Private SPOL::ControllerList Parameters;
	_Public QMap<QString, QString>* Context;
	CREATE_SPOLControllerNewFunction(Speaking);
	CREATE_SPOLControllerNewFunction(AnyText);
	CREATE_SPOLControllerNewFunction(Background);
	CREATE_SPOLControllerNewFunction(Sound);
	CREATE_SPOLControllerNewFunction(State);
	CREATE_SPOLControllerNewFunction(Animation);
	_Public virtual bool parseLine(const QString& line) PureVirtual;
};


