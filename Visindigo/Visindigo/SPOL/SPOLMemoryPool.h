#pragma once
#include "SPOLBaseObject.h"
//SPOL内存池提供对基本SPOL数据类型的存储
//SPOL对象不通过内存池存储，使用树状结构管理内存
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
typedef unsigned long long SPOLMemoryPointer;
enum class SPOLMemoryBaseType {
	Int, Float, String, None, Error
};

class SPOLMemoryPool{
	_Public static SPOLMemoryPool* Instance;
	_Public QQueue<SPOLBaseObject*> ParaStack;
	_Public SPOLBaseObject* ReturnRegister;
	_Public QList<SPOLInt>  IntArea;
	_Public QList<SPOLFloat> DoubleArea;
	_Public QList<SPOLString> StringArea;
	_Public unsigned int emptyArea = 0;
	_Public float gcPercent = 0.5;
	_Public def_init SPOLMemoryPool();
	//malloc返回的指针其引用计数默认为1，不要再counterAdd
	_Public SPOLMemoryPointer malloc(SPOLMemoryBaseType type);
	_Public void garbageCollect();
	_Public void counterAdd(SPOLMemoryPointer p);
	_Public void counterSub(SPOLMemoryPointer p);
	_Public bool getInt(SPOLMemoryPointer p, long long* value);
	_Public bool getFloat(SPOLMemoryPointer p, double* value);
	_Public bool getString(SPOLMemoryPointer p, QString* value);
	_Public void saveInt(SPOLMemoryPointer p, long long value);
	_Public void saveFloat(SPOLMemoryPointer p, double value);
	_Public void saveString(SPOLMemoryPointer p, QString value);
	_Public static SPOLMemoryBaseType getPointerType(SPOLMemoryPointer p);
	_Public void pushStack(SPOLBaseObject*);
	_Public SPOLBaseObject* popStack();
};

