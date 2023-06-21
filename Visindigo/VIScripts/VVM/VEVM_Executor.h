#pragma once
#include "VISObject_Standard.h"
#include "VISObject_Number.h"
#include "VEVM_MemPool.h"
#include "VEVM_Instruction.h"
#include "VEVM_Exception.h"
#include <stack> 
class VEVM_Executor {
public:
	static VEVM_Executor* Instance;
public:
	VEVM_Executor() {
		Instance = this;
	}
	void exec() {
		VISObject* p = VEVM_MemPool::Instance->findDefObject("print");

	}
	void call() {
		VEVM_Instruction::List* ins = VEVM_MemPool::Instance->getInstructions();
		for (int i = 0; i < ins->size(); i++) {
			VEVM_Instruction::Instruction* p = &(ins->at(i));
			switch (p->type) {
			case VEVMInsType::LOAD_CONST_NUM:
				if (p->para2.find(".") == std::string::npos) {
					VISObject* r = new VISObject_FLOAT(std::stod(p->para2));
					VEVM_MemPool::Instance->saveObjectFromRawAsConst(r, p->para1);
				}
				else {
					VISObject*r = VEVM_MemPool::Instance->newIntObject(std::stoi(p->para1));
					VEVM_MemPool::Instance->saveObjectFromRawAsConst(r, p->para1);
				}
				break;
			case VEVMInsType::LOAD_CONST_STR:
				VISObject* r = new VISObject_STRING(p->para2);
				VEVM_MemPool::Instance->saveObjectFromRawAsConst(r, p->para1);
				break;
			case VEVMInsType::NEW_LOCAL_TYPE_NAME:
				VEVM_MemPool::Instance->newLocalObject(p->para1, p->para2);
				break;
			case VEVMInsType::NEW_THIS_TYPE_NAME:
				VEVM_MemPool::Instance->newThisObject(p->para1, p->para2);
				break;
			case VEVMInsType::CALL:
				if (p->para2 == "__assign__") {
					VISObjectPointer* p1 = VEVM_MemPool::Instance->findObjectWithName(p->para1);
					VISObjectPointer* p2 = VEVM_MemPool::Instance->findObjectWithName(p->para2);
					p1->onAssign(p2);
				}
				else if (p->para2 == "__is__") {
					VEVM_MemPool::Instance->LOAD_LOCAL_PARA("value");
					VISObjectPointer* p1 = VEVM_MemPool::Instance->findLocalObject("value");
					VISObjectPointer* p2 = VEVM_MemPool::Instance->findObjectWithName(p->para2);
					if (p1->getPointer() == p2->getPointer()) {
						VISObject* t = VEVM_MemPool::Instance->getConstObject("True");
						VEVM_MemPool::Instance->SET_RETURN(VISObjectPointer("rtn", t));
					}
					else {
						VISObject* t = VEVM_MemPool::Instance->getConstObject("False");
						VEVM_MemPool::Instance->SET_RETURN(VISObjectPointer("rtn", t));
					}
				}
			}
			
		}
		VEVM_MemPool::Instance->popInstructions();
	}

};