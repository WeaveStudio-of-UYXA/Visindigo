#pragma once
#include <QtCore>
#include <QtWidgets>

class VIQtExtMethod :public QObject
{
	Q_OBJECT
public:
	static QString QSSExtension(QString QSS, QWidget* widget) {
		while (true) {
			if (QSS.contains("AUTO_") && QSS.contains("_PR")) {
				int Index_b = QSS.indexOf("AUTO_");
				int Index_e = QSS.indexOf("_PR");
				QString pr = QSS.mid(Index_b + 5, Index_e - Index_b - 5);
				QSS.replace("AUTO_" + pr + "_PR", QString::number((int)(pr.toFloat() * widget->height() / 100)) + "px");
			}
			else {
				break;
			}
		}
		return QSS;
	}
};