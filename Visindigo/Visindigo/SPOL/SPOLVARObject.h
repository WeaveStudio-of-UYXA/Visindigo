#pragma once
#include "SPOLObject.h"

class SPOLExec_VAR :public SPOLExecObject {
	_Public QString Value;
	_Public SPOLExec_VAR* Quote;
	_Public ENUM VARType{
		Number = 0,
		String = 1,
		Quote = 2,
		Other = 3,
	};
	_Public SPOLExec_VAR::VARType ValueType;
	_Public def_init SPOLExec_VAR(SPOLExecObject* parent = NULLOBJECT) :SPOLExecObject(ExecType::Var, parent) {};
	_Public SPOLExecObject exec(SPOLExecObject*);
	_Public void setValue(double value);
	_Public void setValue(QString value);
	_Public void setValue(SPOLExec_VAR* value);
	_Public double getNumber();
	_Public QString getString();
	_Public SPOLExecObject* getQuote();
	_Public VARType getType();
	_Public bool virtual is(SPOLExec_VAR* var);
	_Public bool virtual moreThan(SPOLExec_VAR* var);
	_Public bool virtual lessThan(SPOLExec_VAR* var);
	_Public bool virtual notMoreThan(SPOLExec_VAR* var);
	_Public bool virtual notLessThan(SPOLExec_VAR* var);
	_Public void virtual copyFrom(SPOLExec_VAR* var);
};

class SPOLExec_CLASS :public SPOLExec_VAR {
	_Public def_init SPOLExec_CLASS(SPOLExecObject* parent = NULLOBJECT) :SPOLExec_VAR(parent) { Type = ExecType::Class; initTHIS(); };
	_Private void initTHIS();
	_Public void appendClassChild(SPOLExecObject* child);
};


class SPOLExec_CPR :public SPOLExecObject {
	_Public ENUM CPRType{
		more = 0,
		less = 1,
		equal = 2,
		notEqual = 3,
	};
	_Public SPOLExecObject* Target1;
	_Public SPOLExecObject* Target2;
	_Public def_init SPOLExec_CPR(SPOLExecObject* parent = Q_NULLPTR) :SPOLExecObject(ExecType::Logic, parent) {};
};