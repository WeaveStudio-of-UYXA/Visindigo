#pragma once
#include "VISObject.h"
#include <stack>
#include <map>

/*VISObject原则：
* 1.只允许从VEVM_Memory内部new VISObject
* 2.VEVM_Memory内部可以任用VISObject*，但对外只允许传递VISObjectPointer或其指针
*/
class VEVM_Memory {
public:
	std::map<ConstObjName, VISObject*> ConstPool;
	std::list<VISObject*> StaticPool;
	VISObject* DefRoot;
	std::list<VISObject*> MemPool;
	std::stack<std::map<PointerName, VISObjectPointer>> LocalStack;
	std::stack<VISObjectPointer> ParaStack;
	std::stack<VISObject*> CallStack;
	std::stack<VISObject*> ThisStack;
	VISObjectPointer ReturnObject;
	static VEVM_Memory* Instance;
	VEVM_Memory() {
		DefRoot = new VISObject();
		DefRoot->setCTypeName("%defRoot%");
	}
	VISObject* getDefRoot() {
		return DefRoot;
	}
};