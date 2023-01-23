#pragma once
#include "SPOLMemoryPool.h"

enum class SPOLVarType {
	Int, Float, String, Char, None
};
class SPOLBaseVar
{
	_Private SPOLMemoryPointer THIS = 0;
	_Private bool IsQuote = false;
	_Private SPOLVarType ValueType = SPOLVarType::None;
	_Public def_init SPOLBaseVar(long long value);
	_Public def_init SPOLBaseVar(double value);
	_Public def_init SPOLBaseVar(QString value);
	_Public def_init SPOLBaseVar(char value);
	_Public def_init SPOLBaseVar();
	_Public def_copy SPOLBaseVar(const SPOLBaseVar& obj);
	_Public def_del ~SPOLBaseVar();
	_Private void setValueType(SPOLVarType type);
	_Public SPOLVarType getValueType();
	_Public bool isNone();
	_Public long long getInt();
	_Public double getFloat();
	_Public QString getString();
	_Public bool isQuote();
};