#pragma once
#include "VISObject.h"
#include "VISObject_Standard.h"
#include "VEVM_MemPool.h"
class VISObject_Class :public VISPermissonsObject {
public:
	bool haveSuperClass = false;
	VISObject_Class() {
		currentTypeName = "class";
	}
	VISObjectPointer superClass;
	ObjectFType superClassName;
	VISObject_Class(const VISObject_Class& obj) {
		this->currentTypeName = obj.currentTypeName;
		this->callable = obj.callable;
		for (auto it = obj.childrenList.begin(); it != obj.childrenList.end(); it++) {
			this->childrenList[it->first] = VEVM_MemPool::Instance->newObjectFromPointer(it->second, it->first);
		}
		if (obj.haveSuperClass) {
			this->haveSuperClass = true;
			this->superClassName = obj.superClassName;
			this->superClass = VEVM_MemPool::Instance->newObject(obj.superClassName, "super");
			this->childrenList["super"] = this->superClass;
		}
	}
	void setSuperClassName(ObjectFType name) {
		haveSuperClass = true;
		superClassName = name;
	}
};