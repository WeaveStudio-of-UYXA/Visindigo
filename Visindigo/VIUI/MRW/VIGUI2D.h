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
	VIGUI2DWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		
	}
};