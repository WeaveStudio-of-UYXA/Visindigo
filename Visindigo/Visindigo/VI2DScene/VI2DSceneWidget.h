#pragma once
#include "private/VI2DScene_m.h"

class VI2DSceneWidget : public QGraphicsView
{
	Q_OBJECT;
	_Public QLabel* TestLabel;
	_Public QGraphicsProxyWidget* TestProxy;
	_Public QGraphicsScene* Scene;
	_Public def_init VI2DSceneWidget(QWidget* parent = VI_NULLPTR) :QGraphicsView(parent) {
		Scene = new QGraphicsScene();
		this->setScene(Scene);
		TestLabel = new QLabel("TestLabel");
		TestProxy = Scene->addWidget(TestLabel);
		//TestProxy->setPos(0, 0);
	};
};