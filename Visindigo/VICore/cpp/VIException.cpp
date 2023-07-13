#include "../VIException.h"
#include "../VIConsole.h"

void VIException::print() {
	VIConsole::printLine(VIConsole::inErrorStyle("Visindigo encountered an unhandled exception: " + ExceptionName));
	VIConsole::printLine(VIConsole::inWarningStyle("Reason: " + Reason));
	VIConsole::printLine(VIConsole::inWarningStyle("Help: " + Help));
}