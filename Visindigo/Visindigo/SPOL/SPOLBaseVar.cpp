#include "SPOLBaseVar.h"
def_init SPOLBaseVar::SPOLBaseVar(long long value) {
	setValueType(SPOLVarType::Int);
	THIS = MemPool->malloc(SPOLMemoryBaseType::Int);
	MemPool->saveInt(THIS, value);
}
def_init SPOLBaseVar::SPOLBaseVar(double value) {
	setValueType(SPOLVarType::Float);
	THIS = MemPool->malloc(SPOLMemoryBaseType::Float);
	MemPool->saveFloat(THIS, value);
}
def_init SPOLBaseVar::SPOLBaseVar(QString value) {
	setValueType(SPOLVarType::String);
	THIS = MemPool->malloc(SPOLMemoryBaseType::String);
	MemPool->saveString(THIS, value);
}
def_init SPOLBaseVar::SPOLBaseVar(char value) {
	setValueType(SPOLVarType::Char);
	THIS = MemPool->malloc(SPOLMemoryBaseType::String);
	MemPool->saveString(THIS, QString(value));
}
def_init SPOLBaseVar::SPOLBaseVar() {
	setValueType(SPOLVarType::None);
}
def_copy SPOLBaseVar::SPOLBaseVar(const SPOLBaseVar& obj) {
	THIS = obj.THIS;
	IsQuote = true;
	ValueType = obj.ValueType;
	MemPool->counterAdd(THIS);
}
def_del SPOLBaseVar::~SPOLBaseVar() {{
	MemPool->counterSub(THIS);
}