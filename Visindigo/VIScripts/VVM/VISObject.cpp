#include "VISObject.h"
#include "VEVM_MemPool.h"
VISObjectPointer::VISObjectPointer() {
	this->pointerName = "";
	this->objectFType = "";
	this->RawObject = nullptr;
}
VISObjectPointer::VISObjectPointer(std::string type, std::string name, VISObject* pointer) {
	this->pointerName = name;
	this->objectFType = type;
	this->RawObject = pointer;
	this->RawObject->refCount++;
}
VISObjectPointer::VISObjectPointer(const VISObjectPointer& obj) {
	this->pointerName = obj.pointerName;
	this->objectFType = obj.objectFType;
	this->RawObject = obj.RawObject;
	this->RawObject->refCount++;
}
void VISObjectPointer::__assign__(VISObjectPointer* obj) {
	if (fixedType) {
		if (obj->objectFType != this->objectFType && obj->objectFType != "None") {
			throw std::exception("Type mismatch");
		}
	}
	this->RawObject->refCount--;
	if (this->RawObject->refCount == 0) {
		VEVM_MemPool::Instance->freeObject(this->RawObject);
	}
	this->RawObject = obj->RawObject;
	this->RawObject->refCount++;
}
VISObjectPointer::~VISObjectPointer() {
	this->RawObject->refCount--;
	if (this->RawObject->refCount == 0) {
		VEVM_MemPool::Instance->freeObject(this->RawObject);
	}
}

VISObject::VISObject() {
	currentTypeName = "__UN__";
}
VISObject::VISObject(const VISObject& obj) {
	this->currentTypeName = obj.currentTypeName;
	this->callable = obj.callable;
	for (auto it = obj.childrenList.begin(); it != obj.childrenList.end(); it++) {
		this->childrenList[it->first] = VEVM_MemPool::Instance->newObjectFromPointer(it->second, it->first);
	}
}

void VISObject::onCall(std::string name = ""){
	//当调用VISObject的onCall时，默认是对象的最后一层，即此对象含有函数，进而调用函数对象。
	if (name == "") {
		if (!internalCall()) {
			throw std::exception("The function object is not implemented");
		}
	}
	else {
		auto i = childrenList.find(name);
		if (i != childrenList.end()) {
			if (i->second->callable) {
				i->second->onCall();
			}
			else {
				throw std::exception("Object is not callable");
			}
		}
		else {
			if (!internalCall(name)) {
				throw std::exception("Object dose not have the function");
			}
		}
	}
};

VISObjectPointer* VISObject::findObjectWithName(std::string objName) {
	std::vector<std::string> nameSplit;
	VEVM_StdExtension::splitStdString(objName, ".", nameSplit);
	int layer = 0;
	int length = nameSplit.size();
	if (childrenList.find(nameSplit[layer]) != childrenList.end()) {
		if (layer = length - 1) {
			return &(childrenList[nameSplit[layer]]);
		}
		else {
			return childrenList[nameSplit[layer]]->findObjectWithName(&nameSplit, ++layer, length);
		}
	}
	throw std::exception("Object name not found");
}
VISObjectPointer* VISObject::findObjectWithName(std::vector<std::string>* nameSplit, int layer, int length) {
	if (childrenList.find((*nameSplit)[layer]) != childrenList.end()) {
		if (layer = length - 1) {
			return &(childrenList[(*nameSplit)[layer]]);
		}
		else {
			return childrenList[(*nameSplit)[layer]]->findObjectWithName(nameSplit, ++layer, length);
		}
	}
}
bool VISObject::internalCall(std::string name = "") { 
	return false; 
}
void VISObject::refCountAdd() {
	this->refCount++;
	this->refCountT++;
}
void VISObject::refCountSub() {
	this->refCount--;
	this->refCountT--;
}
void VISObject::refCountTestSub() {
	this->refCountT--;
}
void VISObject::refCountTestAdd() {
	this->refCountT++;
}
void VISObject::refCountTestRedo() {
	this->refCountT = this->refCount;
}

void VISObject::setCTypeName(ObjectCType name) {
	this->currentTypeName = name;
}