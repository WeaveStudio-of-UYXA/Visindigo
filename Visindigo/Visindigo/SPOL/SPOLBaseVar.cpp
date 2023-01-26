#include "SPOLBaseVar.h"
def_init SPOLBaseVar::SPOLBaseVar(long long value) {
	if (!isNone()) { MemPool->counterSub(Address); }
	setValueType(SPOLVarType::Int);
	if (value >= - 63 && value < 256) {
		Address = MemPool_IntPointer(value + 63);
	}
	Address = MemPool->malloc(SPOLMemoryBaseType::Int);
	MemPool->saveInt(Address, value);
}
def_init SPOLBaseVar::SPOLBaseVar(double value) {
	if (!isNone()) { MemPool->counterSub(Address); }
	setValueType(SPOLVarType::Float);
	Address = MemPool->malloc(SPOLMemoryBaseType::Float);
	MemPool->saveFloat(Address, value);
}
def_init SPOLBaseVar::SPOLBaseVar(QString value) {
	if (!isNone()) { MemPool->counterSub(Address); }
	setValueType(SPOLVarType::String);
	Address = MemPool->malloc(SPOLMemoryBaseType::String);
	MemPool->saveString(Address, value);
}
def_init SPOLBaseVar::SPOLBaseVar() {
	setValueType(SPOLVarType::None);
}
def_copy SPOLBaseVar::SPOLBaseVar(const SPOLBaseVar& obj) {
	Address = obj.Address;
	ValueType = obj.ValueType;
	MemPool->counterAdd(Address);
}
def_del SPOLBaseVar::~SPOLBaseVar() {
	MemPool->counterSub(Address);
}
void SPOLBaseVar::setValueType(SPOLVarType type) {
	ValueType = type;
}
void SPOLBaseVar::copyFrom(SPOLBaseVar* obj) {
	MemPool->counterSub(Address);
	Address = obj->Address;
	ValueType = obj->ValueType;
	MemPool->counterAdd(Address);
}
bool SPOLBaseVar::isNone() {
	return Address == 0;
}