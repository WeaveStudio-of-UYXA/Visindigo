#pragma once
#include "../VICore/VICore.h"
#include <QtWidgets>
#include <QtGui>

class VIWidget :public QFrame, public VIBaseObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VIWidget(QWidget* parent = VI_NULLPTR) :QFrame(parent) {
		if (parent == VI_NULLPTR) {
			this->setWindowTitle("Visindigo Widget");
		}
		
	}
};