// I know you want to see this file, but it is not for users to use.
// This file is only be used by VIECMAScripts
#pragma once
#include "../VIConsole.h"
#include "../VIVersion.h"
#include "../VIMultiPlatform.h"
#include <QtQml>

class VIPublicAPI private_VIECMA_Console :public VIConsole
{
	Q_OBJECT;
	VI_OBJECT;
	_Public Q_INVOKABLE def_init private_VIECMA_Console() {
		setObjectName("Console");
	}
	_Slot QString getColorString(QString rawText, int r, int g, int b) {
		return VIConsole::getColorString(rawText, QColor(r, g, b), VIConsole::Style::Normal);
	}
	_Slot QString inWarningStyle(QString rawText) {
		return VIConsole::inWarningStyle(rawText);
	}
	_Slot QString inErrorStyle(QString rawText) {
		return VIConsole::inErrorStyle(rawText);
	}
	_Slot QString inSuccessStyle(QString rawText) {
		return VIConsole::inSuccessStyle(rawText);
	}
	_Slot QString inNoticeStyle(QString rawText) {
		return VIConsole::inNoticeStyle(rawText);
	}
	_Slot void printLine(QString msg) {
		VIConsole::printLine(msg);
	}
};