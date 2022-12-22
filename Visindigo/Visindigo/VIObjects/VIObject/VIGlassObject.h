#pragma once
#include <QtCore>
#include "../../../CommonEdit/CECore/CEMacro.h"

#define p_VI_REF_SIGNAL(methodName) p_VI_REF_##methodName
#define def_REF(methodName, ...) Q_SIGNAL void p_VI_REF_SIGNAL(methodName)(__VA_ARGS__); virtual void methodName(__VA_ARGS__) = 0
#define emit_REF(methodName, ...) emit p_VI_REF_SIGNAL(methodName)(__VA_ARGS__);
#define def_REF_SS(methodName) def_REF(methodName){EMIT_REF(methodName)}
#define p_TEMPLATE_1(Type) template<typename Type>
#define p_TEMPLATE_1_NAME T
#define Template p_TEMPLATE_1(p_TEMPLATE_1_NAME)
#define TempType p_TEMPLATE_1_NAME
class VIGlassObject :public QObject
{
	Q_OBJECT;
	Private VIGlassObject* Another;
	Public VIGlassObject(QObject* parent = Q_NULLPTR) {
		this->setParent(parent);
	};
	Public def setAnother(VIGlassObject* another) {
		this->Another = another;
	}
	Public def_REF(getAnother) {
		emit_REF(getAnother);
	}
	Public Template void newAnother() {
		Another = new TempType;
	}
};