#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "GUI2D/VI2DGUI.h"
#include "MRWGlobal.h"
class VIGUI2DWidget :public QWidget
{
	Q_OBJECT
signals:
	void mousePressed();
public:
	QList<VITextLabel*> Label;
	VIAnimationEventProcess* Process;
	VIGUI2DWidget(QWidget* parent, VIAnimationEventProcess* process) :QWidget(parent) {
		Process = process;
	}
public slots:
	void newVITextLabel(VITextLabel** p) {
		*p = new VITextLabel(this, Process);
		Label.append(*p);
	}
	void mousePressEvent(QMouseEvent* event) {
		emit mousePressed();
	}
	void resizeEvent(QResizeEvent* event) {
		for (auto i = Label.begin(); i != Label.end(); i++) {
			(*i)->resizeEvent();
		}
	}
};