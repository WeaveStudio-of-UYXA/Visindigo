#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "GUI2D/VI2DGUI.h"
#include "Scene3D/VIScene3DBase.h"
#include "MRWGlobal.h"

class VIGUI2DWidget :public QWidget
{
	Q_OBJECT
signals:
	void mousePressed();
public:
	VI3DWidget* Widget3D;
	QList<VI2DGUILabel*> LabelList;

	VIGUI2DWidget(QWidget* parent) :QWidget(parent) {
		Widget3D = new VI3DWidget(this);
	}
	void mousePressEvent(QMouseEvent* event) {
		emit mousePressed();
	}
public slots:
	void newVITextLabel(VITextLabel** p) {
		*p = new VITextLabel(this);
		LabelList.append(*p);
	}
	void newVIPictureLabel(VIPictureLabel** p) {
		*p = new VIPictureLabel(this);
		LabelList.append(*p);
	}
	void removeVI2DGUILabel(VI2DGUILabel* p) {
		LabelList.removeOne(p);
	}
	void resizeEvent(QResizeEvent* event) {
		for (auto i = LabelList.begin(); i != LabelList.end(); i++) {
			(*i)->resizeEvent();
		}
		Widget3D->resize(this->width(), this->height());
	}
};