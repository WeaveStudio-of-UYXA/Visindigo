#pragma once
#include <exception>
#include <string>
class VEVM_Exception : public std::exception {
public:
	enum class VEVM_ExceptionFrom {
		MemPool,
		Executor,
		Kernel,
		Extend,
	};
	enum class VEVM_ExceptionType {
		CNF_LVoSO,
		CNF_TO,
		O_NC,
		NO_NC,
		D_B_Z,
		SO_Rd,
		NV_DN,
		WT,
	};
	VEVM_ExceptionFrom from;
	VEVM_ExceptionType type;

	std::string targetObjName;
public:
	VEVM_Exception() {
	}
	VEVM_Exception(const char* msg) : std::exception(msg) {
	}
	VEVM_Exception(const std::string& msg) : std::exception(msg.c_str()) {
	}
	VEVM_Exception(VEVM_ExceptionFrom from, VEVM_ExceptionType type, std::string tarObjName) : std::exception(tarObjName.c_str())
		, type(type), from(from)
		, targetObjName(tarObjName) {
	}
	std::string detail() {
		std::string rtn;
		switch (from) {
		case VEVM_ExceptionFrom::MemPool:
			rtn += "Memory Pool: ";
			break;
		case VEVM_ExceptionFrom::Executor:
			rtn += "Executor: ";
			break;
		case VEVM_ExceptionFrom::Kernel:
			rtn += "Kernel: ";
			break;
		case VEVM_ExceptionFrom::Extend:
			rtn += "Extend: ";
			break;
		}
		switch (type) {
		case VEVM_ExceptionType::CNF_LVoSO:
			rtn += "Cannot find local variable or static object: " + targetObjName;
			break;
		case VEVM_ExceptionType::CNF_TO:
			rtn += "Unable to find object in 'this': " + targetObjName;
			break;
		case VEVM_ExceptionType::O_NC:
			rtn += "Object is not callable: " + targetObjName;
			break;
		case VEVM_ExceptionType::NO_NC:
			rtn += "None object is not callable: " + targetObjName;
			break;
		case VEVM_ExceptionType::D_B_Z:
			rtn += "Divide by zero: " + targetObjName;
			break;
		case VEVM_ExceptionType::SO_Rd:
			rtn += "Static object redefinition: " + targetObjName;
			break;
		case VEVM_ExceptionType::NV_DN:
			rtn += "New variable duplicate name: " + targetObjName;
			break;
		case VEVM_ExceptionType::WT:
			rtn += "Wrong type: " + targetObjName;
			break;
		}
	}
};