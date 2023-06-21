#pragma once
#include "VISObject_Standard.h"
#include "VEVM_Instruction.h"
#include "VEVM_MemPool.h"
#include "VEVM_Executor.h"
class VISObject_Function :public VISStandardObject {
	VEVM_Instruction::List instructions;
public:
	VISObject_Function() {
		currentTypeName = "function";
	}
	VEVM_Instruction::List getInstructions() {
		return instructions;
	}
	bool internalCall(std::string name = "") {
		VEVM_MemPool::Instance->pushInstructions(&instructions);
		VEVM_Executor::Instance->call();
		return true;
	}
};