#pragma once
#include "VISObject.h"

class VISObjectOperator {
public:
	template<typename T>static T* newVISObject() {
		return new T();
	}
	template<typename T>static T* newVISObjectFrom(const T& obj) {
		return new T(obj);
	}
};