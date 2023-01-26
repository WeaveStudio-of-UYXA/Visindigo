#pragma once
#include "SPOLMemoryPool.h"
#define SPOL_NONE 0
enum class SPOLVarType {
	Int, Float, String, None
};
//SPOLBaseVar是和SPOL内存池直接打交道的类，被SPOLVar进一步封装，严禁直接操作此类
//SPOLBaseVar保存的值可以任取其C++指针读取但不得修改，若要修改值应该使用SPOLBaseVar成员函数
//因为修改值需要触发深拷贝并修改引用计数。
class SPOLBaseVar
{
	_Private SPOLMemoryPointer Address = 0;
	_Private SPOLVarType ValueType = SPOLVarType::None;
	_Public def_init SPOLBaseVar(long long value);
	_Public def_init SPOLBaseVar(double value);
	_Public def_init SPOLBaseVar(QString value);
	_Public def_init SPOLBaseVar();
	_Public def_copy SPOLBaseVar(const SPOLBaseVar& obj);
	_Public def_del ~SPOLBaseVar();
	_Private void setValueType(SPOLVarType type);
	_Public void copyFrom(SPOLBaseVar* obj);
	_Public SPOLVarType getValueType();
	_Public bool isNone();
	_Public long long getInt();
	_Public double getFloat();
	_Public QString getString();
};