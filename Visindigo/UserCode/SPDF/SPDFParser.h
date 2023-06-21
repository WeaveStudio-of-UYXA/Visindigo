#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "SPDFTerminal.h"
#include "SPDFWorkingEnv.h"

class SPOLInterpreter;
class SPDFAbstractControllerParser :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class SPOLInterpreter;
	VI_ProtectedProperty(QString, ControllerName);
	VI_ProtectedFlag(FunctionLike);
	VI_ProtectedProperty(QColor, ControllerColor);
	VI_ProtectedFlag(DefaultColor);
	_Protected SPDFParserResultList Parameters;
	_Public QMap<QString, QString>* Context;
	_Public def_init SPDFAbstractControllerParser() {
		ControllerName = "Unknown";
		FunctionLike = false;
		ControllerColor = QColor(0, 0, 0);
		DefaultColor = true;
	}
	_Private virtual bool parseLine(const QString& line) final {
		int cnLength = ControllerName.length();
		QString pureLine = "";
		if (FunctionLike) {
			pureLine = line.mid(cnLength + 1, line.length() - cnLength - 2);
			return onParseLine(pureLine);
		}
		else {
			pureLine = line.mid(cnLength, line.length() - cnLength);
			return onParseLine(pureLine);
		}
	}
	_Public virtual bool onParseLine(const QString& line) PureVirtual;
	_Public virtual SPDFParserResultList* getParameters() {
		return &Parameters;
	}

};

class SPDFVIESParserContainer :public SPDFAbstractControllerParser
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QJSValue VIES_SPDFParser;
	_Public QJSValue VIES_onParseLine;
	_Public QJSEngine* Engine;
	_Public def_init SPDFVIESParserContainer(QJSValue parser) {
		Engine = parser.engine();
		VIES_SPDFParser = parser;
		VIES_onParseLine = parser.property("onParseLine");
		ControllerName = parser.property("ControllerName").toString();
		FunctionLike = parser.property("FunctionLike").toBool();
	}
	_Public virtual bool onParseLine(const QString& line) override {
		QJSValueList args;
		args << line;
		QJSValue ParaMapList = Engine->newArray();
		VIES_SPDFParser.setProperty("Parameters", ParaMapList);
		QJSValue result = VIES_onParseLine.callWithInstance(VIES_SPDFParser, args);
		return result.toBool();
	}
	_Public virtual SPDFParserResultList* getParameters() override {
		QJSValue ParaMapList = VIES_SPDFParser.property("Parameters");
		int length = ParaMapList.property("length").toInt();
		for (auto i = 0; i < length; i++) {
			QJSValue VIESObj = ParaMapList.property(i);
			SPDFParserResult obj;
			obj.MethodName = VIESObj.property("MethodName").toString();
			obj.NoWait = VIESObj.property("NoWait").toBool();
			obj.Parameters = VIESObj.property("Parameters").toVariant().toMap();
			Parameters.append(obj);
		}
		return &Parameters;
	}
};