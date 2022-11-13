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
	QLabel* DebugInfoLabel;
	VIAnimationEventProcess* Process;
	VIGUI2DWidget(QWidget* parent, VIAnimationEventProcess* process) :QWidget(parent) {
		Process = process;
		DebugInfoLabel = new QLabel(this);
		DebugInfoLabel->setObjectName("DebugInfo");
		DebugInfoLabel->setStyleSheet("QLabel#DebugInfo{font-size:30px;color:#0CDB23;font-family:'Microsoft YaHei'}");
		DebugInfoLabel->resize(200, 30);
	}
public slots:
	void newVITextLabel(VITextLabel** p) {
		*p = new VITextLabel(this, Process);
		Label.append(*p);
	}
	void mousePressEvent(QMouseEvent* event) {
		emit mousePressed();
	}
	void setFrame(float frame) {
		DebugInfoLabel->setText(QString::number(frame) + " EPPS");
	}
	void resizeEvent(QResizeEvent* event) {
		for (auto i = Label.begin(); i != Label.end(); i++) {
			(*i)->resizeEvent();
		}
	}
};