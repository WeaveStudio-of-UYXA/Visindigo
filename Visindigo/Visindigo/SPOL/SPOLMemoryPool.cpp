#include "SPOLMemoryPool.h"
def_init SPOLMemoryPool::SPOLMemoryPool() {
	for (int i = - 63; i < 256; i++) {
		IntArea.append(SPOLInt{ i, 2 });
	}
}
SPOLMemoryPointer SPOLMemoryPool::malloc(SPOLMemoryBaseType type) {
	SPOLMemoryPointer pointer = 0;
	switch (type) {
	case SPOLMemoryBaseType::Int:
		for (auto i = 0; i < IntArea.length(); i++) {
			if (IntArea.at(i).counter == 0) {
				return MemPool_IntPointer(i);
			}
		}
		IntArea.append(SPOLInt{ 0, 1 });
		pointer = IntArea.length() * 11;
		break;
	case SPOLMemoryBaseType::Float:
		for (auto i = 0; i < DoubleArea.length(); i++) {
			if (DoubleArea.at(i).counter == 0) {
				return MemPool_FloatPointer(i);
			}
		}
		DoubleArea.append(SPOLFloat{ 0, 1 });
		pointer = DoubleArea.length() * 13;
		break;
	case SPOLMemoryBaseType::String:
		for (auto i = 0; i < StringArea.length(); i++) {
			if (StringArea.at(i).counter == 0) {
				return MemPool_StringPointer(i);
			}
		}
		StringArea.append(SPOLString{ "", 1});
		pointer = StringArea.length() * 17;
		break;
	default:
		break;
	}
	return pointer;
}
void SPOLMemoryPool::counterAdd(SPOLMemoryPointer p) {
	if (MemPool_IsIntPoiner(p)) {
		IntArea[MemPool_IntIndex(p)].counter++;
	}
	else if (MemPool_IsFloatPoiner(p)) {
		DoubleArea[MemPool_FloatIndex(p)].counter++;
	}
	else if (MemPool_IsStringPoiner(p)) {
		StringArea[MemPool_StringIndex(p)].counter++;
	}
	else {
		PASS;
	}
}
void SPOLMemoryPool::counterSub(SPOLMemoryPointer p) {
	if (MemPool_IsIntPoiner(p)) {
		IntArea[MemPool_IntIndex(p)].counter--;
	}
	else if (MemPool_IsFloatPoiner(p)) {
		DoubleArea[MemPool_FloatIndex(p)].counter--;
	}
	else if (MemPool_IsStringPoiner(p)) {
		StringArea[MemPool_StringIndex(p)].counter--;
	}
	else {
		PASS;
	}
	if ((float)emptyArea / (IntArea.length() + DoubleArea.length() + StringArea.length() ) > gcPercent) {
		for (auto i = IntArea.begin(); i != IntArea.end();) {
			if (i->counter == 0) {
				i = IntArea.erase(i);
			}
			else {
				i++;
			}
		}
		for (auto i = DoubleArea.begin(); i != DoubleArea.end();) {
			if (i->counter == 0) {
				i = DoubleArea.erase(i);
			}
			else {
				i++;
			}
		}
		for (auto i = StringArea.begin(); i != StringArea.end();) {
			if (i->counter == 0) {
				i = StringArea.erase(i);
			}
			else {
				i++;
			}
		}
	}
}
bool SPOLMemoryPool::getInt(SPOLMemoryPointer p, long long* value) {
	if (MemPool_IsIntPoiner(p)) {
		*value = IntArea.at(MemPool_IntIndex(p)).Value;
		return true;
	}
	else {
		return false;
	}
}
bool SPOLMemoryPool::getFloat(SPOLMemoryPointer p, double* value) {
	if (MemPool_IsFloatPoiner(p)) {
		*value = DoubleArea.at(MemPool_FloatIndex(p)).Value;
		return true;
	}
	else {
		return false;
	}
}

bool SPOLMemoryPool::getString(SPOLMemoryPointer p, QString* value) {
	if (MemPool_IsStringPoiner(p)) {
		*value = StringArea.at(MemPool_StringIndex(p)).Value;
		return true;
	}
	else {
		return false;
	}
}
void SPOLMemoryPool::saveInt(SPOLMemoryPointer p, long long value) {
	if (MemPool_IsIntPoiner(p)) {
		IntArea[MemPool_IntIndex(p)].Value = value;
	}
	else {
		PASS;
	}
}
void SPOLMemoryPool::saveFloat(SPOLMemoryPointer p, double value) {
	if (MemPool_IsFloatPoiner(p)) {
		DoubleArea[MemPool_FloatIndex(p)].Value = value;
	}
	else {
		PASS;
	}
}
void SPOLMemoryPool::saveString(SPOLMemoryPointer p, QString value) {
	if (MemPool_IsStringPoiner(p)) {
		StringArea[MemPool_StringIndex(p)].Value = value;
	}
	else {
		PASS;
	}
}
SPOLMemoryBaseType getPointerType(SPOLMemoryPointer p) {
	if (MemPool_IsIntPoiner(p)) {
		return SPOLMemoryBaseType::Int;
	}
	else if (MemPool_IsFloatPoiner(p)) {
		return SPOLMemoryBaseType::Float;
	}
	else if (MemPool_IsStringPoiner(p)) {
		return SPOLMemoryBaseType::String;
	}
	else {
		return SPOLMemoryBaseType::None;
	}
}