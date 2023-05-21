#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "Global.h"
#if DEPLOY == WINDOWS_DEPLOY
namespace VIUI {
	class VIPlayerWidget :public QWidget {
		Q_OBJECT;
		_Public def_init VIPlayerWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {}
	};
}
#endif