#pragma once
#include "SPOLObject.h"
#define TEMPOBJ true
#define COMBINE true
union SPOLExec_VAR_BaseTypeUnion {
	long long Int;
	double Float;
	bool Bool;
	QString* String;
	SPOLExecObject* Quote;
};
class SPOLExec_VAR :public SPOLExecObject {
	_Public SPOLExec_VAR_BaseTypeUnion Value;
	_Public ENUM VARType{
		Int, Float, String, Bool, Quote, None,
		List, Map,
		Error,
	};
	_Private bool IsLiteralTempVar = false;
	_Public SPOLExec_VAR::VARType ValueType = VARType::None;
	_Public def_init SPOLExec_VAR(double value, bool isTemp = false, SPOLExecObject* parent = NULLOBJECT) 
		:SPOLExecObject(ExecType::Var, parent) { IsLiteralTempVar = isTemp; setValue(value); };
	_Public def_init SPOLExec_VAR(long long value, bool isTemp = false, SPOLExecObject* parent = NULLOBJECT) 
		:SPOLExecObject(ExecType::Var, parent) { IsLiteralTempVar = isTemp; setValue(value); };
	_Public def_init SPOLExec_VAR(bool value, bool isTemp = false, SPOLExecObject* parent = NULLOBJECT) 
		:SPOLExecObject(ExecType::Var, parent) { IsLiteralTempVar = isTemp; setValue(value); };
	_Public def_init SPOLExec_VAR(QString value, bool isTemp = false, SPOLExecObject* parent = NULLOBJECT) 
		:SPOLExecObject(ExecType::Var, parent) { IsLiteralTempVar = isTemp; setValue(value); };
	_Public def_init SPOLExec_VAR(SPOLExecObject* value, bool isTemp, SPOLExecObject* parent) 
		:SPOLExecObject(ExecType::Var, parent) { IsLiteralTempVar = isTemp; setValue(value); };
	_Public def_init SPOLExec_VAR(SPOLExecObject* parent = NULLOBJECT) :SPOLExecObject(ExecType::Var, parent) {};
	_Public def_del ~SPOLExec_VAR();
	_Public inline bool isTempVar();
	_Public inline bool isNone();
	_Public inline bool isError();
	_Public inline void setAsTempVar();
	_Public void setValue(double value);
	_Public void setValue(long long value);
	_Public void setValue(bool value);
	_Public void setValue(QString value);
	_Public void setValue(SPOLExec_VAR* value);
	_Public long long getInt();
	_Public double getFloat();
	_Public QString getString();
	_Public bool getBool();
	_Public SPOLExecObject* getQuote();
	_Public VARType getType();
	_Public SPOLExec_VAR* add(SPOLExec_VAR* var);
	_Public SPOLExec_VAR* subtract(SPOLExec_VAR* var);
	_Public SPOLExec_VAR* multiply(SPOLExec_VAR* var);
	_Public SPOLExec_VAR* divide(SPOLExec_VAR* var);
	_Public SPOLExec_VAR* andTo(SPOLExecObject* var);
	_Public SPOLExec_VAR* orTo(SPOLExecObject * var);
	_Public SPOLExec_VAR* notTo(SPOLExecObject* var);
	_Public SPOLExec_VAR* equal(SPOLExec_VAR* var, bool combine);
	_Public SPOLExec_VAR* moreThan(SPOLExec_VAR* var, bool combine);
	_Public SPOLExec_VAR* lessThan(SPOLExec_VAR* var, bool combine);
	_Public SPOLExec_VAR* notMoreThan(SPOLExec_VAR* var);
	_Public SPOLExec_VAR* notLessThan(SPOLExec_VAR* var);
	_Public SPOLExec_VAR* assign(SPOLExec_VAR* var);
};

class SPOLExec_VAR_NONE :public SPOLExec_VAR{
	_Public def_init SPOLExec_VAR_NONE(SPOLExecObject * parent = NULLOBJECT) :SPOLExec_VAR(parent) { ValueType = VARType::None; }
};
class SPOLExec_LIST :public SPOLExec_VAR {
	_Public def_init SPOLExec_LIST(SPOLExecObject* parent = NULLOBJECT) :SPOLExec_VAR(parent) { ValueType = VARType::List; }
	_Public void setValue(SPOLExec_LIST* value);
	_Public SPOLExec_LIST* add(SPOLExec_VAR* obj);
	_Public SPOLExec_LIST* add(SPOLExec_LIST* obj);
	_Public SPOLExec_VAR* remove(SPOLExec_VAR* obj);
	_Public SPOLExec_VAR* remove(int index);
	_Public SPOLExec_VAR* get(int index);
	_Public int size();
};