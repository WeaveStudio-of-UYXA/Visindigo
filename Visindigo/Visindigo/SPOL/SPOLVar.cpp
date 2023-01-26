#include "SPOLVar.h"
SPOLBaseVar* SPOLVar::getValuePointer() {
	return &value;
}
def_init SPOLVar::SPOLVar() {
	value = SPOLBaseVar();
}
void SPOLVar::__var__(SPOLCallable* self) {
	SPOLList* para = new SPOLList();
	SPOLVar* var = new SPOLVar();
}
def_init SPOLList::SPOLList() {
	value = {};
}
void SPOLList::__var__(SPOLCallable* self) {
	PASS;
}