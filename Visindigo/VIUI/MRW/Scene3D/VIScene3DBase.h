#pragma once
#include <Qt3DCore>
#include <Qt3DExtras>
#include <QtWidgets>
#include <QtCore>

class VI3DScene :public QWidget
{
	Q_OBJECT
public:
	Qt3DExtras::Qt3DWindow* View;
	VI3DScene(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
	}
};