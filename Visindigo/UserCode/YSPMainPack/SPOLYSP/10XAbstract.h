#pragma once
#include "../../SPDF/SPDF.h"

namespace YSP_10X {
	class YSPAbstractSPOLController :public VIObject
	{
		Q_OBJECT;
		VI_OBJECT;
		_Public QString ControllerName = "YSPAbstractSPOLController";
		_Public SPDFParaMap Parameters;
		_Public QStringList NeededParaNames;
		_Public bool NoWait = false;
		_Public def_init YSPAbstractSPOLController(VIObject* parent = VI_NULLPTR) :VIObject(parent) {};
		_Public virtual bool initParaNames(QStringList& names) PureVirtual;
		_Public virtual bool fromSPDFParserResult(SPDFParserResult& result) PureVirtual;
		_Public virtual SPDFParserResult toSPDFParserResult() PureVirtual;
	};
}