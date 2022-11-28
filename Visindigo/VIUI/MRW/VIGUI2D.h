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
	QList<VI2DGUILabel*> Label;

	VIAnimationEventProcess* Process;
	VIGUI2DWidget(QWidget* parent, VIAnimationEventProcess* process) :QWidget(parent) {
		Widget3D = new VI3DWidget(this);
		Process = process;
	}
	void mousePressEvent(QMouseEvent* event) {
		emit mousePressed();
	}
public slots:
	void newVITextLabel(VITextLabel** p) {
		*p = new VITextLabel(this, Process);
		Label.append(*p);
	}
	void newVIPictureLabel(VIPictureLabel** p) {
		*p = new VIPictureLabel(this, Process);
		Label.append(*p);
	}
	void resizeEvent(QResizeEvent* event) {
		for (auto i = Label.begin(); i != Label.end(); i++) {
			(*i)->resizeEvent();
		}
		Widget3D->resize(this->width(), this->height());
	}
};