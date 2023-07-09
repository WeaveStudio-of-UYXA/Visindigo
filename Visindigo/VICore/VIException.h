#pragma once
#include "VIObject.h"
#include "VIConsole.h"
#include <exception>
class VIException
{
	_Public enum class Type{
		None,
		DivideByZero,
		DimensionError,
		BehaviorError,
		IndexOutOfRange,
		NullPointer,
		FrameworkNotInit,
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
	void print() {
		VIConsole::printLine(VIConsole::inErrorStyle("Visindigo encountered an unhandled exception: " + ExceptionName));
		VIConsole::printLine(VIConsole::inWarningStyle("Reason: " + Reason));
		VIConsole::printLine(VIConsole::inWarningStyle("Help: " + Help));
	}
};

class VIDimensionError : public VIException {
	_Public def_init VIDimensionError(const QString& rsn, const QString& help = "") : VIException(rsn, help) {
		ExceptionType = Type::DimensionError;
		ExceptionName = "DimensionError";
	};
};