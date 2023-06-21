#pragma once
#include "VEVMMacro.h"
#include <string>
#include <vector>
#include <map>
#include <exception>
#include "VEVMStdExtension.h"
class VISObject;
class VEVM_MemPool;
class VEVM_Executor;
class VISObjectOperator;
class VEVM_Memory;
class VISDefConstructor;

class VISObjectPointer{
	PointerName pointerName;
	ObjectFType objectFType;
	bool fixedType = false;
	VISObject *RawObject;
public:
	VISObjectPointer();
	VISObjectPointer(ObjectFType type, PointerName name, VISObject* pointer);
	VISObjectPointer(const VISObjectPointer& obj);
	~VISObjectPointer();
	PointerName getObjectName() {
		return pointerName;
	}
	void __fixedType__(std::string type) {
		if (fixedType) {
			throw std::exception("Type already fixed");
		}
		fixedType = true;
		objectFType = type;
	}
	VISObject* getPointer() { return RawObject; };
	void __assign__(VISObjectPointer* obj);
	VISObject * operator->() { return RawObject; }
};

//此类只对MemPool、Executor、Pointer可见
class VISObject {
	friend class VEVM_MemPool;
	friend class VEVM_Executor;
	friend class VISObjectPointer;
	friend class VISObjectOperator;
	friend class VEVM_Memory;
	friend class VISDefConstructor;
protected:
	ObjectCType currentTypeName;
	unsigned long long refCount = 0;
	unsigned long long refCountT = 0;
	std::map<std::string, VISObjectPointer> childrenList;
	bool callable = false;
	VISObject();
	VISObject(const VISObject& obj);
	//onCall函数禁止直接调用，必须由MemPool预先管理This、Para、Call、Try四个栈
	//当调用VISObject的onCall时，默认是对象的最后一层，即此对象含有函数，进而调用函数对象。
	virtual void onCall(std::string name = "") final;
	VISObjectPointer* findObjectWithName(std::string objName);
	VISObjectPointer* findObjectWithName(std::vector<std::string>* nameSplit, int layer, int length);
	//内部调用函数用于函数对象从C++上实现，即重载internalCall并返回true
	//也用于作为类的对象进行函数C++重定向，如判别name为某某的时候定位到类内的某某C++函数。请注意务必返回true
	//作为函数对象的VIS的internalCall被默认实现为将对象保存的指令用于调用指令模块的执行函数，用户可重载此实现。
	virtual bool internalCall(std::string name = "");
	void refCountAdd();
	void refCountSub();
	void refCountTestSub();
	void refCountTestAdd();
	void refCountTestRedo();
	void setCTypeName(ObjectCType name);
};



