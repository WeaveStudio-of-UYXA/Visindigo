#pragma once
#include <QtCore>
#include "../../../CommonEdit/CECore/CEMacro.h"

#define p_VI_REF_SIGNAL(methodName) p_VI_REF_##methodName
#define def_REF(methodName, ...) Q_SIGNAL void p_VI_REF_SIGNAL(methodName)(__VA_ARGS__); void methodName(__VA_ARGS__)
#define emit_REF(methodName, ...) emit p_VI_REF_SIGNAL(methodName)(__VA_ARGS__);
#define def_REF_SS(methodName) def_REF(methodName){emit_REF(methodName)}
#define p_VI_REF_TARGET_NAME p_VI_REF_TARGET
#define GLASS_TYPE(typeName) Public_ typeName* p_VI_REF_TARGET_NAME;
#define set_REF(target) p_VI_REF_TARGET_NAME = target
#define build_REF(methodName, connectType, ...) connect(this, SIGNAL(p_VI_REF_SIGNAL(methodName)(__VA_ARGS__)), p_VI_REF_TARGET_NAME, SLOT(methodName(__VA_ARGS__)), connectType)
#define build_REF_D(methodName, ...) build_REF(methodName, Qt::DirectConnection, __VA_ARGS__)
#define p_TEMPLATE_1(Type) template<typename Type>
#define p_TEMPLATE_1_NAME T
#define VITemplate p_TEMPLATE_1(p_TEMPLATE_1_NAME)
#define VITempType p_TEMPLATE_1_NAME
