#pragma once
#include "private/VI2DScene_m.h"

class VI2DSceneWidget : public QGraphicsView
{
	Q_OBJECT;
	_Public QLabel* TestLabel;
	_Public QGraphicsProxyWidget* TestProxy;
	_Public QGraphicsScene* Scene;
	_Signal void sceneResized(const QRectF& rect);
	_Public def_init VI2DSceneWidget(QWidget* parent = VI_NULLPTR) :QGraphicsView(parent) {
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		Scene = new QGraphicsScene(this);
		this->setScene(Scene);
		TestLabel = new QLabel("TestLabel");
		TestProxy = Scene->addWidget(TestLabel);
		this->setStyleSheet("VI2DSceneWidget{border:0px solid black;}");
		connect(Scene, &QGraphicsScene::sceneRectChanged, this, &VI2DSceneWidget::sceneResized);
		//底色调成黑的
		this->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
	};
	_Public void resizeEvent(QResizeEvent* event) {
		//重设场景大小
		Scene->setSceneRect(QRect(QPoint(0, 0), event->size()));
		this->setSceneRect(QRect(QPoint(0, 0), event->size()));
		qDebug() << "VI2DSceneWidget::resizeEvent";
	}
	_Public QGraphicsProxyWidget* addWidget(QWidget* widget) {
		return Scene->addWidget(widget);
	}
	_Public void addItem(QGraphicsItem* item) {
		Scene->addItem(item);
	}
};