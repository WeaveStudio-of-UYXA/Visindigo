#pragma once
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include "Visindigo/VICore/VIAnimation.h"
#include "VIJSAPI/VIJSGlobal.h"
class VI2DGUILabel :public QLabel
{
	Q_OBJECT
public:
	QWidget* Parent;
	VIAnimationEventProcess* Process;
	bool Wait = false;
	bool SKIP = false;
	bool FINISH = false;
	QGraphicsOpacityEffect* Opacity;
	float px, py, pw, ph;
	QString StyleSheets;
	VI2DGUILabel(QWidget* WidgetParent, VIAnimationEventProcess* AniParent) {
		Parent = WidgetParent;
		Process = AniParent;
		this->setParent(Parent);
		Opacity = new QGraphicsOpacityEffect(this);
		this->setGraphicsEffect(Opacity);
		Opacity->setOpacity(1);
		px = 0.1; py = 0.2; pw = 0.8; ph = 0.6;
	}
};