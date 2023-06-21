#pragma once
#include "VISObject.h"
#include "VEVM_MemPool.h"
#include "VEVM_Executor.h"
#include <fstream>
class VIExecutionVirtualMachine {
public:
	VEVM_MemPool* memPool;
	VEVM_Executor* executor;
	VIExecutionVirtualMachine() {
		memPool = new VEVM_MemPool();
		executor = new VEVM_Executor();
	}
	void loadVISIFile()
};