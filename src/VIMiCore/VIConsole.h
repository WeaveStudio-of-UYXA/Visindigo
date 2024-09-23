#pragma once
#include "VIMacro.h"
#include <QtCore>
#include <QColor>
class VIMiCoreAPI VIConsole{
	_Public enum class Color {
		None, Black, Gray, Red, LightRed,
		Green, LightGreen, Yellow, LightYellow,
		Blue, LightBlue, Purple, LightPurple,
		Cyan, LightCyan, LightGray, White
	};
	_Public enum class Style {
		Normal, Bold, Italic, Underline, Splash, Inverse, Strikethrough
	};
	_Public static QString getColorString(QString rawText, VIConsole::Color color, QList<VIConsole::Style> styleList = { VIConsole::Style::Normal });
	_Public static QString getColorString(QString rawText, VIConsole::Color color, VIConsole::Style style = VIConsole::Style::Normal);
	_Public static QString getColorString(QString rawText, QColor rgb, QList<VIConsole::Style> styleList = { VIConsole::Style::Normal });
	_Public static QString getColorString(QString rawText, QColor rgb, VIConsole::Style style = VIConsole::Style::Normal);
	_Public static QString getLine();
	_Public static QString inWarningStyle(QString rawText);
	_Public static QString inErrorStyle(QString rawText);
	_Public static QString inSuccessStyle(QString rawText);
	_Public static QString inNoticeStyle(QString rawText);
	_Public static QString getRawText(QString colorString);
	_Public static void print(QString msg);
	_Public static void printBinary(const QByteArray& data);
	_Public template <typename T> static inline void printMemory(const T* data) {
		printBinary(QByteArray((char*)data, sizeof(T)));
	};
	_Public static unsigned int exec(const QString& cmd);
};
