#pragma once
#include "../../Visindigo/VICore/VICore.h"

class SPDFParserObject 
{
	_Public QString MethodName = "Unknown";
	_Public QMap<QString, QVariant> Parameters;
	_Public bool NoWait = false;
	_Public def_init SPDFParserObject(){}
	_Public def_copy SPDFParserObject(const SPDFParserObject& obj){
		MethodName = obj.MethodName;
		Parameters = obj.Parameters;
		NoWait = obj.NoWait;
	}
	_Public def_move SPDFParserObject(SPDFParserObject&& obj){
		MethodName = obj.MethodName;
		Parameters = obj.Parameters;
		NoWait = obj.NoWait;
	}
	_Public SPDFParserObject& operator=(const SPDFParserObject& obj){
		MethodName = obj.MethodName;
		Parameters = obj.Parameters;
		NoWait = obj.NoWait;
		return *this;
	}
};
typedef QVector<SPDFParserObject> SPDFParserObjectList;
/*
* Abstract Terminal
* 如果用户要从SPDF获得控制数据，必须·继承此类并实现其虚函数
*/
class SPDFAbstractTerminal :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void controllerHandled();
	_Public def_init SPDFAbstractTerminal() {}
	_Slot virtual void onControllers(SPDFParserObjectList* ParserList) PureVirtual;
};