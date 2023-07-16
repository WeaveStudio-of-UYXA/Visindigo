#pragma once
#include <execution>
#include <QtCore>
#include "private/VIMacro.h"
class VIPublicAPI VIException
{
	_Public enum class Type{
		None,
		DivideByZero,
		DimensionError,
		BehaviorError,
		IndexOutOfRange,
		NullPointerError,
		FrameworkNotInit,
		MethodIsInvalid, //Method is not implemented
		SingletonError,
		Others
	};
	VI_ProtectedProperty(QString, Reason);
	VI_ProtectedProperty(QString, Help);
	VI_ProtectedProperty(Type, ExceptionType);
	VI_ProtectedProperty(QString, ExceptionName);
	_Public def_init VIException(const QString& rsn, const QString& help = "") {
		Reason = rsn;
		Help = help;
		ExceptionType = Type::Others;
		ExceptionName = "Others";
	};
	_Public def_copy VIException(const VIException& other) {
		Reason = other.Reason;
		Help = other.Help;
		ExceptionType = other.ExceptionType;
		ExceptionName = other.ExceptionName;
	};
	_Public def_move VIException(VIException&& other) noexcept {
		Reason = other.Reason;
		Help = other.Help;
		ExceptionType = other.ExceptionType;
		ExceptionName = other.ExceptionName;
	};
	void print();
};

class VIPublicAPI VIDimensionError : public VIException {
	_Public def_init VIDimensionError(const QString& rsn, const QString& help = "") : VIException(rsn, help) {
		ExceptionType = Type::DimensionError;
		ExceptionName = "Dimension Error";
	};
};

class VIPublicAPI VISingletonError : public VIException {
	_Public def_init VISingletonError(const QString& rsn, const QString& help = "") : VIException(rsn, help) {
		ExceptionType = Type::SingletonError;
		ExceptionName = "Singleton Error";
	};
};

class VIPublicAPI VINullPointerError :public VIException {
	_Public def_init VINullPointerError(const QString& rsn, const QString& help = "") :VIException(rsn, help) {
		ExceptionType = Type::NullPointerError;
		ExceptionName = "Null Pointer Error";
	}
};