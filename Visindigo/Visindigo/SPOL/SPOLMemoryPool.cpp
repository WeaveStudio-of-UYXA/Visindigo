#include "SPOLMemoryPool.h"

SPOLMemoryPointer SPOLMemoryPool::malloc(SPOLMemoryBaseType type) {
	SPOLMemoryPointer pointer = 0;
	switch (type) {
	case SPOLMemoryBaseType::Int:
		for (auto i = 0; i < IntArea.length(); i++) {
			if (IntArea.at(i).counter == 0) {
				return (i + 1) * 11;
			}
		}
		IntArea.append(SPOLInt{ 0, 1 });
		pointer = IntArea.length() * 11;
		break;
	case SPOLMemoryBaseType::Float:
		for (auto i = 0; i < DoubleArea.length(); i++) {
			if (DoubleArea.at(i).counter == 0) {
				return (i + 1) * 13;
			}
		}
		DoubleArea.append(SPOLFloat{ 0, 1 });
		pointer = DoubleArea.length() * 13;
		break;
	case SPOLMemoryBaseType::String:
		for (auto i = 0; i < StringArea.length(); i++) {
			if (StringArea.at(i).counter == 0) {
				return (i + 1) * 17;
			}
		}
		StringArea.append(SPOLString{ '\0', 1});
		pointer = StringArea.length() * 17;
		break;
	case SPOLMemoryBaseType::Object:
		for (auto i = 0; i < ObjectArea.length(); i++) {
			if (ObjectArea.at(i).counter == 0) {
				delete ObjectArea[i].Value;
				return (i + 1) * 19;
			}
		}
	default:
		break;
	}
	return pointer;
}
void SPOLMemoryPool::counterAdd(SPOLMemoryPointer p) {
	if (p % 11 == 0) {
		IntArea[p / 11 - 1].counter++;
	}
	else if (p % 13 == 0) {
		DoubleArea[p / 13 - 1].counter++;
	}
	else if (p % 17 == 0) {
		StringArea[p / 17 - 1].counter++;
	}
	else if (p % 19 == 0) {
		ObjectArea[p / 19 - 1].counter++;
	}
	else {
		PASS;
	}
}
void SPOLMemoryPool::counterSub(SPOLMemoryPointer p) {
	if (p % 11 == 0) {
		IntArea[p / 11 - 1].counter--;
		emptyArea++;
	}
	else if (p % 13 == 0) {
		DoubleArea[p / 13 - 1].counter--;
		emptyArea++;
	}
	else if (p % 17 == 0) {
		StringArea[p / 17 - 1].counter--;
		emptyArea++;
	}
	else if (p % 19 == 0) {
		ObjectArea[p / 19 - 1].counter--;
		emptyArea++;
	}
	else {
		PASS;
	}
	if ((float)emptyArea / (IntArea.length() + DoubleArea.length() + StringArea.length() + ObjectArea.length()) > gcPercent) {
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
		for (auto i = ObjectArea.begin(); i != ObjectArea.end();) {
			if (i->counter == 0) {
				delete i->Value;
				i = ObjectArea.erase(i);
			}
			else {
				i++;
			}
		}
	}
}
bool SPOLMemoryPool::getInt(SPOLMemoryPointer p, long long* value) {
	if (p % 11 == 0) {
		*value = IntArea.at(p / 11 - 1).Value;
		return true;
	}
	else {
		return false;
	}
}
bool SPOLMemoryPool::getFloat(SPOLMemoryPointer p, double* value) {
	if (p % 13 == 0) {
		*value = DoubleArea.at(p / 13 - 1).Value;
		return true;
	}
	else {
		return false;
	}
}

bool SPOLMemoryPool::getString(SPOLMemoryPointer p, QString* value) {
	if (p % 17 == 0) {
		*value = StringArea.at(p / 17 - 1).Value;
		return true;
	}
	else {
		return false;
	}
}
bool SPOLMemoryPool::getSPOLObject(SPOLMemoryPointer p, SPOLBaseObject** value) {
	if (p % 19 == 0) {
		*value = ObjectArea.at(p / 19 - 1).Value;
		return true;
	}
	else {
		return false;
	}
}
void SPOLMemoryPool::saveInt(SPOLMemoryPointer p, long long value) {
	if (p % 11 == 0) {
		IntArea[p / 11 - 1].Value = value;
	}
	else {
		PASS;
	}
}
void SPOLMemoryPool::saveFloat(SPOLMemoryPointer p, double value) {
	if (p % 13 == 0) {
		DoubleArea[p / 13 - 1].Value = value;
	}
	else {
		PASS;
	}
}
void SPOLMemoryPool::saveString(SPOLMemoryPointer p, QString value) {
	if (p % 17 == 0) {
		StringArea[p / 17 - 1].Value = value.toStdString().c_str();
	}
	else {
		PASS;
	}
}
SPOLMemoryBaseType getPointerType(SPOLMemoryPointer p) {
	if (p == 0) {
		return SPOLMemoryBaseType::None;
	}
	if (p % 11 == 0) {
		return SPOLMemoryBaseType::Int;
	}
	else if (p % 13 == 0) {
		return SPOLMemoryBaseType::Float;
	}
	else if (p % 17 == 0) {
		return SPOLMemoryBaseType::String;
	}
	else if (p % 19 == 0) {
		return SPOLMemoryBaseType::Object;
	}
	else {
		return SPOLMemoryBaseType::Error;
	}
}