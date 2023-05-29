#include "../VIConsole.h"

/*
VIConsole
*/
QString VIConsole::getColorString(QString rawText, VIConsole::Color color, QList<VIConsole::Style> styleList ) {
	QString styleString = "";
	switch (color) {
	case Color::None:
		styleString = "\033[0";
		break;
	case Color::Black:
		styleString = "\033[30";
		break;
	case Color::Gray:
		styleString = "\033[1;30";
		break;
	case Color::Red:
		styleString = "\033[31";
		break;
	case Color::LightRed:
		styleString = "\033[1;31";
		break;
	case Color::Green:
		styleString = "\033[32";
		break;
	case Color::LightGreen:
		styleString = "\033[1;32";
		break;
	case Color::Yellow:
		styleString = "\033[33";
		break;
	case Color::LightYellow:
		styleString = "\033[1;33";
		break;
	case Color::Blue:
		styleString = "\033[34";
		break;
	case Color::LightBlue:
		styleString = "\033[1;34";
		break;
	case Color::Purple:
		styleString = "\033[35";
		break;
	case Color::LightPurple:
		styleString = "\033[1;35";
		break;
	case Color::Cyan:
		styleString = "\033[36";
		break;
	case Color::LightCyan:
		styleString = "\033[1;36";
		break;
	case Color::LightGray:
		styleString = "\033[37";
		break;
	case Color::White:
		styleString = "\033[1;37";
		break;
	default:
		styleString = "\033[0";
		break;
	}
	for (int i = 0; i < styleList.size(); i++) {
		switch (styleList[i]) {
		case Style::Normal:
			styleString += ";0";
			break;
		case Style::Bold:
			styleString += ";1";
			break;
		case Style::Italic:
			styleString += ";3";
			break;
		case Style::Underline:
			styleString += ";4";
			break;
		case Style::Splash:
			styleString += ";5";
			break;
		case Style::Inverse:
			styleString += ";7";
			break;
		case Style::Strikethrough:
			styleString += ";9";
			break;
		}
	}
	styleString += "m";
	return styleString + rawText + "\033[0m";
}

QString VIConsole::getColorString(QString rawText, VIConsole::Color color, VIConsole::Style style) {
	return getColorString(rawText, color, QList<VIConsole::Style>({ style }));
}

QString VIConsole::getColorString(QString rawText, QColor rgb, QList<VIConsole::Style> styleList) {
	QString styleString = QString::asprintf("\033[38;2;%d;%d;%d", rgb.red(), rgb.green(), rgb.blue());
	for (int i = 0; i < styleList.size(); i++) {
		switch (styleList[i]) {
		case Style::Normal:
			styleString += ";0";
			break;
		case Style::Bold:
			styleString += ";1";
			break;
		case Style::Italic:
			styleString += ";3";
			break;
		case Style::Underline:
			styleString += ";4";
			break;
		case Style::Splash:
			styleString += ";5";
			break;
		case Style::Inverse:
			styleString += ";7";
			break;
		case Style::Strikethrough:
			styleString += ";9";
			break;
		}
	}
	styleString += "m";
	return styleString + rawText + "\033[0m";
}

QString VIConsole::getColorString(QString rawText, QColor rgb, VIConsole::Style style) {
	return getColorString(rawText, rgb, QList<VIConsole::Style>({ style }));
}

QString VIConsole::inWarningStyle(QString rawText) {
	return getColorString(rawText, QColor(255,253,85), Style::Bold);
}

QString VIConsole::inErrorStyle(QString rawText) {
	return getColorString(rawText, Color::Red, Style::Bold);
}

QString VIConsole::inSuccessStyle(QString rawText) {
	return getColorString(rawText, Color::Green, Style::Bold);
}

QString VIConsole::inNoticeStyle(QString rawText) {
	return getColorString(rawText, Color::Blue, Style::Bold);
}

void VIConsole::printLine(QString msg) {
	qDebug().noquote() << msg;
}