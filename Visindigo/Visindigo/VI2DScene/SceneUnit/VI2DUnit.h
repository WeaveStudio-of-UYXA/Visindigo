#pragma once
#include "../macro/VI2DScene_m.h"
#include "../../VICore/VIAnimation.h"

class VI2DUnit :public QObject
{
	Q_OBJECT;
	_Public VIOpacityAniBehavior* OpacityAni = new VIOpacityAniBehavior(this);
	_Public QGraphicsItem* GraphicsItem = Q_NULLPTR;
	_Public def_init VI2DUnit(QObject* parent = Q_NULLPTR) :QObject(parent) {}
	_Public void setParentUnit(VI2DUnit* parent) {
		GraphicsItem->setParentItem(parent->GraphicsItem);
	}
	_Public QGraphicsItem* getGraphicsItem() {
		return GraphicsItem;
	}
	_Public ~VI2DUnit() {
		if (GraphicsItem != Q_NULLPTR) {
			delete GraphicsItem;
		}
	}
	_Public void setOpacity(float op) {
		this->GraphicsItem->setOpacity(op);
	}
};

class VI2DTextUnit :public VI2DUnit 
{
	Q_OBJECT;
	_Private QGraphicsTextItem* Item = new QGraphicsTextItem();
	_Public def_init VI2DTextUnit(QObject* parent):VI2DUnit(parent) {
		GraphicsItem = Item;
	}
	_Public def_init VI2DTextUnit(VI2DUnit* parent) : VI2DUnit(parent) {
		GraphicsItem = Item;
		Item->setParent(parent);
	}
	_Public void setText(QString& str) {
		Item->setPlainText(str);
	}
};