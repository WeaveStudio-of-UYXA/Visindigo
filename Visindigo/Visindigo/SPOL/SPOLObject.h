#pragma once
#include "../../../CommonEdit/CECore/CEMacro.h"
#include "macro/SPOL_m.h"
#include <QtCore>

class SPOLExecObject :public QObject {
	Q_OBJECT;
	_Public ENUM ExecType{
		Var = 0,
		Func = 1,
		Logic = 2
	};
	_Public QString Name;
	_Public QString TypeName;
	_Public QString Path;
	_Public SPOLExecObject* Parent;
	_Public QList<SPOLExecObject*> Child;
	_Public ExecType Type;
	_Public def_init SPOLExecObject(ExecType type, SPOLExecObject* parent = Q_NULLPTR) :QObject(parent) { Type = type; };
	_Public void setParent(SPOLExecObject*);
	_Protected void addChild(SPOLExecObject*);
	_Protected void removeChild(SPOLExecObject*);
	_Public SPOLExecObject* getParent();
	_Public QList<SPOLExecObject*> getChildren();
	_Public bool hasChild(QString fullName, SPOLExecObject** returnObj);
	_Public bool hasChild(QStringList* nameList, QStringList::Iterator* name, SPOLExecObject** returnObj);
	_Public virtual SPOLExecObject exec() {};
	_Public virtual SPOLExecObject onExec() {};
};
typedef QList<SPOLExec_VAR::VARType> SPOLVarTypeList;
class SPOLExec_VAR :public SPOLExecObject {
	Q_OBJECT;
	_Public QStringList Value;
	_Public bool IsList = false;
	_Public ENUM VARType{
		Number = 0,
		String = 1,
		Other = 3,
	};
	_Public SPOLVarTypeList ValueType;
	_Public def_init SPOLExec_VAR(SPOLExecObject* parent = Q_NULLPTR) :SPOLExecObject(ExecType::Var, parent) {};
	_Public SPOLExecObject exec() override;
	_Public SPOLExecObject onExec() override;
	_Public void setValue(double value, int index = 0);
	_Public void setValue(QString value, int index = 0);
	_Public void setValue(QStringList value, SPOLVarTypeList type);
	_Public double getNumber(int index = 0);
	_Public QString getString(int index = 0);
	_Public QStringList getOther();
	_Public VARType getType(int index = 0);
	_Public SPOLVarTypeList getTypeList();
	_Public bool is(SPOLExec_VAR* var);
	_Public bool moreThan(SPOLExec_VAR* var);
	_Public bool lessThan(SPOLExec_VAR* var);
	_Public bool notMoreThan(SPOLExec_VAR* var);
	_Public bool notLessThan(SPOLExec_VAR* var);
	_Public bool copyFrom(SPOLExec_VAR* var);
};
class SPOLExec_CPR :public SPOLExecObject {
	Q_OBJECT;
	_Public ENUM CPRType{
		more = 0,
		less = 1,
		equal = 2,
		notEqual = 3,
	};
	_Public SPOLExecObject* Target1;
	_Public SPOLExecObject* Target2;
	_Public def_init SPOLExec_CPR(SPOLExecObject* parent = Q_NULLPTR) :SPOLExecObject(ExecType::Logic, parent) {};
	_Public SPOLExecObject exec() override;
	_Public SPOLExecObject onExec() override;
};