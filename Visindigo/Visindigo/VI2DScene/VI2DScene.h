#pragma once
#include "macro/VI2DScene_m.h"
#include "SceneUnit/VI2DUnit.h"
class VI2DScene :public QGraphicsScene
{
	Q_OBJECT;
	_Public QVector<VI2DUnit*> UnitList; //我们真的需要这玩意吗
	_Public def_init VI2DScene(QObject* parent = Q_NULLPTR) :QGraphicsScene(parent) {	
	}
};

class VI2DWidget :public QGraphicsView
{
	Q_OBJECT;
	_Public VI2DScene* Scene;
	_Public def_init VI2DWidget(QWidget* parent = Q_NULLPTR) :QGraphicsView(parent) {
		this->Scene = new VI2DScene(this);
		this->setMinimumSize(800, 600);
		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->setScene(Scene);
		QGraphicsTextItem* t = new QGraphicsTextItem();
		t->setHtml("<p align='right'>Hello World Helllllllllll wwwwww</p>");
		t->setFont(QFont("Microsoft YaHei", 20));
		t->adjustSize();
		this->Scene->addItem(t);
	}
	_Public void resizeEvent(QResizeEvent* event) {
		this->setSceneRect(- event->size().width()/2, -event->size().height()/2, event->size().width(), event->size().height());
	}
	_Public void addVI2DUnit(VI2DUnit* unit) {
		this->Scene->addItem(unit->GraphicsItem);
	}
};