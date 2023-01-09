#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "GUI2D/VI2DGUI.h"
#include "Scene3D/VIScene3DBase.h"
#include "MRWGlobal.h"

class VIGUI2DWidget :public QWidget
{
	Q_OBJECT;
	_Signal void mousePressed();
	_Public VI3DWidget* Widget3D;
	_Public QList<VI2DGUILabel*> LabelList;
	_Public def_init VIGUI2DWidget(QWidget* parent) :QWidget(parent) {
		Widget3D = new VI3DWidget(this);
	}
	_Public void mousePressEvent(QMouseEvent* event) {
		emit mousePressed();
	}
	_Slot void newVITextLabel(VITextLabel** p) {
		*p = new VITextLabel(this);
		LabelList.append(*p);
	}
	_Slot void newVIPictureLabel(VIPictureLabel** p) {
		*p = new VIPictureLabel(this);
		LabelList.append(*p);
	}
	_Slot void removeVI2DGUILabel(VI2DGUILabel* p) {
		LabelList.removeOne(p);
	}
	_Slot void resizeEvent(QResizeEvent* event) {
		for (auto i = LabelList.begin(); i != LabelList.end(); i++) {
			(*i)->resizeEvent();
		}
		Widget3D->resize(this->width(), this->height());
	}
};