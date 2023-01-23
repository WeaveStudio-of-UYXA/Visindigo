#pragma once
#include "SPOLBaseObject.h"

struct SPOLInt {
	long long Value;
	int counter;
};
struct SPOLFloat {
	double Value;
	int counter;
};
struct SPOLString {
	QString Value;
	int counter;
};
struct SPOLObj {
	SPOLBaseObject* Value;
	int counter;
};
typedef unsigned long long SPOLMemoryPointer;
enum class SPOLMemoryBaseType {
	Int, Float, String, None, Object, Error
};

class SPOLMemoryPool{
	_Public static SPOLMemoryPool* Instance;
	_Public QList<SPOLInt>  IntArea;
	_Public QList<SPOLFloat> DoubleArea;
	_Public QList<SPOLString> StringArea;
	_Public QList<SPOLObj> ObjectArea;
	_Public unsigned int emptyArea = 0;
	_Public float gcPercent = 0.5;
	_Public SPOLMemoryPointer malloc(SPOLMemoryBaseType type);
	_Public void garbageCollect();
	_Public void counterAdd(SPOLMemoryPointer p);
	_Public void counterSub(SPOLMemoryPointer p);
	_Public bool getInt(SPOLMemoryPointer p, long long* value);
	_Public bool getFloat(SPOLMemoryPointer p, double* value);
	_Public bool getString(SPOLMemoryPointer p, QString* value);
	_Public bool getSPOLObject(SPOLMemoryPointer p, SPOLBaseObject** value);
	_Public void saveInt(SPOLMemoryPointer, long long value);
	_Public void saveFloat(SPOLMemoryPointer, double value);
	_Public void saveString(SPOLMemoryPointer, QString value);
	_Public static SPOLMemoryBaseType getPointerType(SPOLMemoryPointer p);
};

