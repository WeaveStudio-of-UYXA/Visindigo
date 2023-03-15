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

class VI2DView :public QGraphicsView
{
	Q_OBJECT;
	_Public VI2DScene* Scene;
	_Public VI2DTextUnit* t;
	_Public VI2DFrameUnit* debug;
	_Public def_init VI2DView(QWidget* parent = Q_NULLPTR) :QGraphicsView(parent) {
		this->Scene = new VI2DScene(this);
		this->setMinimumSize(1366, 768);
		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->setBackgroundBrush(QBrush(QColor(0, 0, 0, 255)));
		this->setScene(Scene);
		t = new VI2DTextUnit(this);
		t->setTextWidth(300);
		t->setAlignment(Qt::AlignCenter);
		//t->setTextColor(QColor(255, 255, 255, 255));
		Scene->addItem(t->getGraphicsItem());
		debug = new VI2DFrameUnit(this);
		debug->setTextWidth(300);
		debug->setAlignment(Qt::AlignLeft);
		debug->setTextColor(QColor(255, 255, 255, 255));
		Scene->addItem(debug->getGraphicsItem());
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