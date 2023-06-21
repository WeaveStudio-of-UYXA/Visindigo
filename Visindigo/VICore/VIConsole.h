﻿#pragma once
#include "VIObject.h"
#include <QtGui>

class VIConsole : public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public ENUM Color{
		None, Black, Gray, Red, LightRed,
		Green, LightGreen, Yellow, LightYellow,
		Blue, LightBlue, Purple, LightPurple,
		Cyan, LightCyan, LightGray, White
	};
	_Public ENUM Style{
		Normal, Bold, Italic, Underline, Splash, Inverse, Strikethrough
	};
	_Public static QString getColorString(QString rawText, VIConsole::Color color, QList<VIConsole::Style> styleList = { VIConsole::Style::Normal });
	_Public static QString getColorString(QString rawText, VIConsole::Color color, VIConsole::Style style = VIConsole::Style::Normal);
	_Public static QString getColorString(QString rawText, QColor rgb, QList<VIConsole::Style> styleList = { VIConsole::Style::Normal });
	_Public static QString getColorString(QString rawText, QColor rgb, VIConsole::Style style = VIConsole::Style::Normal);
	_Public static QString inWarningStyle(QString rawText);
	_Public static QString inErrorStyle(QString rawText);
	_Public static QString inSuccessStyle(QString rawText);
	_Public static QString inNoticeStyle(QString rawText);
	_Public static void printLine(QString msg);
};