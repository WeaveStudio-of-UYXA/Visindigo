#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "GUI2D/VI2DGUI.h"
#include "MRWGlobal.h"
class VIRuntimeWindow :public QMainWindow
{
	Q_OBJECT
public:
	VIRuntimeWindow(QWidget* parent = 0) : QMainWindow(parent) {
		MRWGlobal::Process = new VIAnimationEventProcess(this);
		//MRWGlobal::Process->start();

		
	}
};

