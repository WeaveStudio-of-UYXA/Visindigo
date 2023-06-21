#pragma once
#include "VISObject.h"
class VISStandardObject :public VISObject {
public:
	VISStandardObject() {
	}
	virtual bool __init__() { return false; };
	virtual bool __del__() { return false; };
	virtual bool __add__() { return false; };
	virtual bool __sub__() { return false; };
	virtual bool __mul__() { return false; };
	virtual bool __div__() { return false; };
	virtual bool __mod__() { return false; };
	virtual bool __pow__() { return false; };
	virtual bool __bool__() { return false; };
	virtual bool __eq__() { return false; };
	virtual bool __ne__() { return false; };
	virtual bool __more__() { return false; };
	virtual bool __less__() { return false; };
	virtual bool __notmo__() { return false; };
	virtual bool __notle__() { return false; };
	virtual bool __and__() { return false; };
	virtual bool __or__() { return false; };
	virtual bool __not__() { return false; };
	virtual bool __str__() { return false; };
	virtual bool __imadd__() { return false; };
	virtual bool __imsub__() { return false; };
	virtual bool __immul__() { return false; };
	virtual bool __imdiv__() { return false; };
	virtual bool __immod__() { return false; };
	virtual bool __call__() { return false; };
	bool internalCall(std::string name = "") {
		if (name == "__init__") { return __init__(); }
		else if (name == "__del__") { return __del__(); }
		else if (name == "__add__") { return __add__(); }
		else if (name == "__sub__") { return __sub__(); }
		else if (name == "__mul__") { return __mul__(); }
		else if (name == "__div__") { return __div__(); }
		else if (name == "__mod__") { return __mod__(); }
		else if (name == "__pow__") { return __pow__(); }
		else if (name == "__bool__") { return __bool__(); }
		else if (name == "__eq__") { return __eq__(); }
		else if (name == "__ne__") { return __ne__(); }
		else if (name == "__more__") { return __more__(); }
		else if (name == "__less__") { return __less__(); }
		else if (name == "__notmo__") { return __notmo__(); }
		else if (name == "__notle__") { return __notle__(); }
		else if (name == "__and__") { return __and__(); }
		else if (name == "__or__") { return __or__(); }
		else if (name == "__not__") { return __not__(); }
		else if (name == "__str__") { return __str__(); }
		else if (name == "__imadd__") { return __imadd__(); }
		else if (name == "__imsub__") { return __imsub__(); }
		else if (name == "__immul__") { return __immul__(); }
		else if (name == "__imdiv__") { return __imdiv__(); }
		else if (name == "__immod__") { return __immod__(); }
		else if (name == "__call__") { return __call__(); }
		else { return false; }
	}
};

class VISPermissonsObject :public VISStandardObject {
public:
	enum class Perm {
		PRIVATE,
		PROTECTED,
		PUBLIC
	};
};