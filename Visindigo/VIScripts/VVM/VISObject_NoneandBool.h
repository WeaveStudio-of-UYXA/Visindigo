#pragma once
#include "VISObject_Standard.h"

class VISObject_NONE :public VISStandardObject {
public:
	VISObject_NONE() {
		objectType = "None";
	}
	void onCall(std::string name = "") {
		throw VEVM_Exception(VEVM_Exception::VEVM_ExceptionFrom::Kernel, VEVM_Exception::VEVM_ExceptionType::NO_NC, "None");
	}
};

class VISObject_BOOL :public VISStandardObject {
public:
	bool value;
	VISObject_BOOL(bool value) {
		objectType = "bool";
		this->value = value;
	}
	void onCall(std::string name = "") {
		throw VEVM_Exception(VEVM_Exception::VEVM_ExceptionFrom::Kernel, VEVM_Exception::VEVM_ExceptionType::NO_NC, "None");
	}
};