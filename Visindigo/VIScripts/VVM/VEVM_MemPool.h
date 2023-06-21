#pragma once
#include "VISObject.h"
#include "VEVM_Instruction.h"
#include <map>
#include <exception>
#include <stack>
#include <vector>
#include <list>
class VEVM_MemPool {
	std::map<std::string, VISObject*> ConstPool;
	std::map<std::string, VISObject*> DefPool;
	VISObject* DefTree;
	std::stack<VEVM_Instruction::List*> InstructionStack;
	std::list<VISObject*> MemPool;
	std::stack<std::map<std::string, VISObjectPointer>> LocalStack;
	std::stack<VISObjectPointer> ParaStack;
	std::stack<VISObject*> CallStack;
	std::stack<VISObject*> ThisStack;
	std::stack<VISObject*> TryStack; 
	VISObjectPointer ReturnObject;
public:
	static VEVM_MemPool* Instance;
public:
	VEVM_MemPool();
	VISObjectPointer newObject(std::string typeName, std::string name) {
		if (typeName != "None") {
			std::vector<std::string> nameSplit;
			VEVM_StdExtension::splitStdString(typeName, ".", nameSplit);
			VISObject* p;
			int layer = 0;
			int length = nameSplit.size();
			if (DefPool.find(nameSplit[layer]) != DefPool.end()) {
				if (layer = length - 1) {
					p = DefPool[nameSplit[layer]];
				}
				else {
					p = DefPool[nameSplit[layer]]->findObjectWithName(&nameSplit, ++layer, length)->getPointer();
				}
			}
			else {
				throw std::exception("Object name not found");
			}
			VISObject* newObject = new VISObject(*p);
			MemPool.push_back(newObject);
			return VISObjectPointer(name, newObject);
		}
		else {
			return VISObjectPointer(name, ConstPool["None"]);
		}
	}
	VISObject* newIntObject(long long value);
	VISObjectPointer newObjectFromPointer(VISObjectPointer objP, std::string name) {
		VISObject* p = objP.getPointer();
		VISObject* newObject = new VISObject(*p);
		MemPool.push_back(newObject);
		return VISObjectPointer(name, newObject);
	}
	VISObjectPointer saveObjectFromRaw(VISObject* objRP, std::string name) {
		MemPool.push_back(objRP);
		return VISObjectPointer(name, objRP);
	}
	void saveObjectFromRawAsDef(VISObject* objRP, std::string name) {
		DefPool[name] = objRP;
	}
	void saveObjectFromRawAsConst(VISObject* objRP, std::string name) {
		ConstPool[name] = objRP;
	}
	VISObject* getConstObject(std::string name) {
		return ConstPool[name];
	}
	void freeObject(VISObject* obj) {
		for (auto i = MemPool.begin(); i != MemPool.end(); i++) {
			if (*i == obj) {
				delete *i;
				MemPool.erase(i);
				return;
			}
		}
	}
	void addLocalObject(std::string name, VISObjectPointer p) {
		if (LocalStack.top().find(name)==LocalStack.top().end()){
			LocalStack.top()[name] = p;
		}
		else {
			throw std::exception("Object name already exists");
		}
	}
	void deleteLocalObject(std::string name) {
		if (LocalStack.top().find(name) != LocalStack.top().end()) {
			LocalStack.top().erase(name);
		}
		else {
			throw std::exception("Object name not found");
		}
	}
	void newLocalObject(std::string typeName, std::string name) {
		addLocalObject(name, newObject(typeName, name));
	}
	void addThisObject(std::string name, VISObjectPointer p) {
		if (ThisStack.top()->childrenList.find(name) == ThisStack.top()->childrenList.end()) {
			ThisStack.top()->childrenList[name] = p;
		}
		else {
			throw std::exception("Object name already exists");
		}
	}
	void deleteThisObject(std::string name) {
		if (ThisStack.top()->childrenList.find(name) != ThisStack.top()->childrenList.end()) {
			ThisStack.top()->childrenList.erase(name);
		}
		else {
			throw std::exception("Object name not found");
		}
	}
	void newThisObject(std::string typeName, std::string name) {
		addThisObject(name, newObject(typeName, name));
	}
	VISObjectPointer* findThisObject(std::string name) {
		return ThisStack.top()->findObjectWithName(name);
	}
	void callThisObject(std::string objName, std::string funcName) {
		VISObjectPointer* thisObj = findThisObject(objName);
		ThisStack.push(thisObj->getPointer());
		ThisStack.top()->onCall(funcName);
	}
	VISObjectPointer* findLocalObject(std::string objName) {
		std::vector<std::string> nameSplit;
		VEVM_StdExtension::splitStdString(objName, ".", nameSplit);
		int layer = 0;
		int length = nameSplit.size();
		if (LocalStack.top().find(nameSplit[layer]) != LocalStack.top().end()) {
			if (layer = length - 1) {
				return &(LocalStack.top()[nameSplit[layer]]);
			}
			else {
				return LocalStack.top()[nameSplit[layer]]->findObjectWithName(&nameSplit, ++layer, length);
			}
		}
		throw std::exception("Object name not found");
	}
	VISObject* findDefObject(std::string objName) {
		std::vector<std::string> nameSplit;
		VEVM_StdExtension::splitStdString(objName, ".", nameSplit);
		int layer = 0;
		int length = nameSplit.size();
		if (DefPool.find(nameSplit[layer]) != DefPool.end()) {
			if (layer = length - 1) {
				return DefPool[nameSplit[layer]];
			}
			else {
				return DefPool[nameSplit[layer]]->findObjectWithName(&nameSplit, ++layer, length)->getPointer();
			}
		}
		else {
			throw std::exception("Object name not found");
		}
	}
	VISObjectPointer* findObjectWithName(std::string objName) {
		std::vector<std::string> nameSplit;
		VEVM_StdExtension::splitStdString(objName, ".", nameSplit);
		int layer = 0;
		int length = nameSplit.size();
		if (nameSplit[0] == "this") {
			nameSplit.erase(nameSplit.begin());
			return findThisObject(objName);
		}
		else {
			return findLocalObject(objName);
		}
		throw std::exception("Object name not found");
	}
	VISObjectPointer* findPointer(std::string ptName) {
		
	}
	void callStaticObject(std::string objName, std::string funcName) {
		findDefObject(objName)->onCall(funcName);
	}
	void pushInstructions(VEVM_Instruction::List* list) {
		InstructionStack.push(list);
	}
	VEVM_Instruction::List* getInstructions() {
		return InstructionStack.top();
	}
	void popInstructions() {
		InstructionStack.pop();
	}
	void CALL(std::string objName, std::string funcName) {
		ReturnObject = VISObjectPointer("rtn", getConstObject("None"));
		std::vector<std::string> nameSplit;
		VEVM_StdExtension::splitStdString(objName, ".", nameSplit);
		if (nameSplit[0]=="this") { 
			if (nameSplit.size() == 2) {
				ThisStack.top()->onCall(funcName);
			}
			else {
				nameSplit.erase(nameSplit.begin());
				callThisObject(objName, funcName);
			}
		}
		else {
			callStaticObject(objName, funcName);
		}
	}
	void PUSH_PARA(std::string varName) {
		ParaStack.push(*(findObjectWithName(varName)));
	}
	void PUSH_RETURN_PARA() {
		ParaStack.push(ReturnObject);
	}
	void LOAD_LOCAL_PARA(std::string name) {
		addLocalObject(name, ParaStack.top());
		ParaStack.pop();
	}
	void SET_RETURN(VISObjectPointer p) {
		ReturnObject = p;
	}
};