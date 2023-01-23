#include "SPOLObjectPool.h"
SPOLMemoryPool* SPOLMemoryPool::Instance = NULLOBJECT;

void SPOLObjectPool::setExecMain(SPOLExecObject* main) {
	ExecMain = main;
}
bool SPOLObjectPool::hasDefObject(QString name, SPOLExecObject** returnObj){
	QStringList nameList = name.split(".");
	for (auto i = DefPool.begin(); i != DefPool.end(); i++) {
		if (nameList[0] == (*i)->Name) {
			if (nameList.length() >= 1) {
				return (*i)->hasChild(name.section('.', 1, -1), returnObj);
			}
			else { return true; }
		}
	}
	return false;
}
void SPOLObjectPool::addDefObject(SPOLExecObject* defObj) {
	SPOLExecObject* test = NULLOBJECT;
	if (!this->hasDefObject(defObj->Name, &test)) {
		DefPool.append(defObj);
	}
	else {
		PASS;
	}
}
void SPOLObjectPool::addDefObjectTo(SPOLExecObject* defObj, SPOLExecObject* parent) {
	defObj->setParent(parent);
}
void SPOLObjectPool::addDefObjectTo(SPOLExecObject* defObj, QString parentName) {
	SPOLExecObject* parent;
	if (hasDefObject(parentName, &parent)) {
		addDefObjectTo(defObj, parent);
	}
	else {
		PASS;
	}
}