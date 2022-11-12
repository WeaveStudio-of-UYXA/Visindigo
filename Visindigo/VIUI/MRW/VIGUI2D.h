﻿#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "GUI2D/VI2DGUI.h"
#include "MRWGlobal.h"
class VIGUI2DWidget :public QWidget
{
	Q_OBJECT
public:
	QList<VITextLabel*> Label;
	VIAnimationEventProcess* Process;
	VIGUI2DWidget(QWidget* parent,VIAnimationEventProcess* process) :QWidget(parent) {
		Process = process;
	}
public slots:
	void newVITextLabel(VITextLabel** p) {
		*p = new VITextLabel(this, Process);
	}
};