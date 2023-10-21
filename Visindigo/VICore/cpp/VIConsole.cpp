#include "../VIConsole.h"
#include <iostream>
/*
VIConsole
*/
QString VIConsole::getColorString(QString rawText, VIConsole::Color color, QList<VIConsole::Style> styleList) {
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

QString VIConsole::getLine() {
	std::string commandStd;
	std::getline(std::cin, commandStd);
	return QString::fromLocal8Bit(QByteArray::fromStdString(commandStd));
}
QString VIConsole::inWarningStyle(QString rawText) {
	return getColorString(rawText, QColor(255, 253, 85), Style::Bold);
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

void VIConsole::printBinary(const QByteArray& data) {
	if (data.isEmpty()) { return; }
	printLine("L\\B\t00  01  02  03  04  05  06  07  |  00 01 02 03 04 05 06 07  |");
	printLine("---------------------------------------------------------------------");
	int B = 0;
	int L = 0;
	QString rawText = "";
	QString chatText = "";
	bool UninitializedMemory = false;
	for (auto i = data.begin(); i != data.end(); i++) {
		if (*i < 0 || *i>255) {
			rawText.append("??  ");
			UninitializedMemory = true;
		}
		else {
			rawText.append(QString::number(*i, 16).rightJustified(2, '0').toUpper() + "  ");
		}
		if (*i >= 0x20 && *i <= 0x7E) {
			chatText.append(" " % QChar(*i) % " ");
		}
		else if (*i == 0x0A) {
			chatText.append("\\n ");
		}
		else if (*i == 0x0D) {
			chatText.append("\\r ");
		}
		else if (*i == 0x09) {
			chatText.append("\\t ");
		}
		else if (*i < 0 || *i>255) {
			chatText.append("?? ");
		}
		else {
			chatText.append(" . ");
		}
		B++;
		L++;
		if (B == 8) {
			printLine(QString::number(L, 10) % "\t" % rawText % "|  " % chatText % " |");
			rawText = "";
			chatText = "";
			B = 0;
		}
	}
	if (B != 0) {
		for (int i = 0; i < 8 - B; i++) {
			rawText.append("    ");
			chatText.append("   ");
		}
		printLine(QString::number(L, 10) % "\t" % rawText % "|  " % chatText % " |");
	}
	printLine("---------------------------------------------------------------------");
	if (UninitializedMemory) {
		printLine(inWarningStyle("Warning: Uninitialized memory detected.(Part marked as '??')\nIf this data directly comes from a struct or class, please ignore this issue"));
	}
}

unsigned int VIConsole::exec(const QString& cmd) {
	return system(cmd.toLocal8Bit().data());
}