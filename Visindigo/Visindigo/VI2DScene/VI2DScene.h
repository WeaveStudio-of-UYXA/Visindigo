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
		VI2DTextUnit* t = new VI2DTextUnit(this);
		t->setTextWidth(300);
		t->setTextAni("Hello World----------", 300, 1000);
		t->setAlignment(Qt::AlignCenter);
		Scene->addItem(t->getGraphicsItem());
	}
	_Public void resizeEvent(QResizeEvent* event) {
		//从QGraphicsItem的坐标系来看，实际上此处更应该将视口中心置于0，0点
		//但为了和传统顶级QWidget坐标兼容，对于QGraphicsScene仍然只采用其第一象限。
		this->setSceneRect(0, 0, event->size().width(), event->size().height());
		QSize size = event->size();
		QList<QObject*> list = this->children();
		for (auto i = list.begin(); i != list.end(); i++) {
			VI2DUnit* unit = dynamic_cast<VI2DUnit*>(*i);
			if (unit != Q_NULLPTR) {
				unit->__onSceneResize(size);
			}
		}
	}
	_Public void addVI2DUnit(VI2DUnit* unit) {
		this->Scene->addItem(unit->GraphicsItem);
	}
};