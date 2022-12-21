#pragma once
#include <QtCore>
#include "../../../CommonEdit/CECore/CEMacro.h"

#define p_VI_INVOKE_SIGNAL(methodName) p_VI_INVOKE_##methodName
#define def_INVOKE(methodName, ...) Q_SIGNAL void p_VI_INVOKE_SIGNAL(methodName)(__VA_ARGS__); virtual void methodName(__VA_ARGS__)
#define EMIT_INVOKE(methodName, ...) emit p_VI_INVOKE_SIGNAL(methodName)(__VA_ARGS__);
#define def_INVOKE_SS(methodName) def_INVOKE(methodName){EMIT_INVOKE(methodName)}
#define p_TEMPLATE_1(Type) template<typename Type>
#define p_TEMPLATE_1_NAME T
#define Template p_TEMPLATE_1(p_TEMPLATE_1_NAME)
#define TempType p_TEMPLATE_1_NAME
class VIInvokeObject :public QObject
{
	Q_OBJECT;
	Private VIInvokeObject* Another;
	Public VIInvokeObject(QObject* parent = Q_NULLPTR) {
		this->setParent(parent);
	};
	Public def setAnother(VIInvokeObject* another) {
		this->Another = another;
	}
	Public def_INVOKE(getAnother) {
		EMIT_INVOKE(getAnother);
	}
	Public def_INVOKE_SS(show);
	Public def_INVOKE(test, void);
	Public Template void newAnother() {
		Another = new TempType;
	}
};