#include "SPOLBaseObject.h"

QString SPOLBaseObject::getObjectName() {
	return ObjectName;
}
void SPOLBaseObject::setObjectName(QString name) {
	ObjectName = name;
}
void SPOLBaseObject::referenceFrom(SPOLBaseObject* obj) {
	QuoteList.append(obj);
	obj->Counter++;
}
void SPOLBaseObject::beReferencedBy(SPOLBaseObject* obj) {
	obj->referenceFrom(this);
}
void SPOLBaseObject::Unreferenced() {
	this->Counter--;
	if (Counter == 0) {
		delete this;
	}
}
SPOLBaseObject::~SPOLBaseObject() {
	for (auto i = QuoteList.begin(); i != QuoteList.end(); i++) {
		(*i)->Counter--;
	}
}