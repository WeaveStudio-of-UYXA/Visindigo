#include "VISObject.h"
#include "VEVM_MemPool.h"
#include "VISObject_Standard.h"
#include "VEVM_Exception.h"
#include <map>

class VISObject_INT :public VISStandardObject {
	long long value;
	VISObject* left;
public:
	VISObject_INT(long long value) { 
		this->objectType = "int";
		this->value = value; 
	}
	long long getValue() { return value; }
	bool internelCall(std::string name) {
		VEVM_MemPool::Instance->LOAD_LOCAL_PARA("value");
		VISObjectPointer* obj = VEVM_MemPool::Instance->findLocalObject("value");
		left = obj->getPointer();
		if (left->objectType == "int" || left->objectType == "float") {
			return VISStandardObject::internalCall(name);
		}
		else {
			throw VEVM_Exception(VEVM_Exception::VEVM_ExceptionFrom::Kernel, VEVM_Exception::VEVM_ExceptionType::WT, obj.getObjectName());
		}
	}
	bool __add__() {
		long long rtn = 0;
		if (left->objectType == "int") {
			VISObject_INT* left_int = (VISObject_INT*)left;
			rtn = value + left_int->getValue();
		}
		else if (left->objectType == "float") {
			//VISObject_FLOAT* left_float = (VISObject_FLOAT*)left;
			//value += left_float->getValue();
		}
		VISObject* ans_p = VEVM_MemPool::Instance->newIntObject(rtn);
		VISObjectPointer p = VEVM_MemPool::Instance->saveObjectFromRaw(ans_p, "rtn");
		VEVM_MemPool::Instance->SET_RETURN(p);
		return true;
	}
public:
};

class VISObject_FLOAT : public VISObject {
	double value;
	VISObject* left;
public:
	VISObject_FLOAT(double value) {
		this->objectType = "float";
		this->value = value;
	}
};

class VISObject_STRING : public VISObject {
	std::string value;
public:
	VISObject_STRING(std::string value) {
	this->objectType = "string";
	this->value = value;
	}
};
