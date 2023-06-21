#include "VEVM_MemPool.h"
#include "VISObject_Number.h"
#include "VISObject_NoneandBool.h"
VEVM_MemPool* VEVM_MemPool::Instance = nullptr;

VEVM_MemPool::VEVM_MemPool() {
	Instance = this;
	VISObject* none = new VISObject_NONE();
	VISObject* true_ = new VISObject_BOOL(true);
	VISObject* false_ = new VISObject_BOOL(false);
	ConstPool["None"] = none;
	ConstPool["True"] = true_;
	ConstPool["False"] = false_;
	for (int i = -30; i < 256; i++) {
		VISObject* obj = new VISObject_INT(i);
		ConstPool["int_" + std::to_string(i)] = obj;
	}
}

VISObject* VEVM_MemPool::newIntObject(long long i) {
	if (i < 256 && i >= -30) {
		return ConstPool["int_" + std::to_string(i)];
	}
	else {
		return new VISObject_INT(i);
	}
}