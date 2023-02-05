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
		OpacityAni->setHost(gBEHAVIOR);
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
	_Public void setOpacityAni(float opStart, float opEnd, VIMilliSecond duration) {
		OpacityAni->setOpacity(opStart, opEnd, duration);
		OpacityAni->active();
	}
};

class VI2DTextUnit :public VI2DUnit 
{
	Q_OBJECT;
	_Public QString AlignHTMLTagS = "<p align='left'>";
	_Public QString AlignHTMLTagE = "</p>";
	_Public VITextAniBehavior* TextAni;
	_Private QGraphicsTextItem* Item = new QGraphicsTextItem();
	_Public def_init VI2DTextUnit(QObject* parent):VI2DUnit(parent) {
		GraphicsItem = Item;
		TextAni = new VITextAniBehavior(this);
		connect(TextAni, SIGNAL(getText(QString)), this, SLOT(setText(QString)));
	}
	_Public def_init VI2DTextUnit(VI2DUnit* parent) : VI2DUnit(parent) {
		GraphicsItem = Item;
		Item->setParent(parent);
	}
	_Slot void setText(QString html) {
		Item->setHtml(AlignHTMLTagS + html + AlignHTMLTagE);
	}
	_Public void setTextAni(QString plainText, VIMilliSecond msPerChar, VIMilliSecond msWait) {
		TextAni->setTextAni(plainText, msPerChar, msWait, false);
		TextAni->active();
	}
	_Public void setTextAniContinue(QString plainText, VIMilliSecond msPerChar, VIMilliSecond msWait) {
		TextAni->setTextAni(plainText, msPerChar, msWait, true);
		TextAni->active();
	}
	_Public void setAlignment(Qt::AlignmentFlag align) {
		switch (align)
		{
		case Qt::AlignLeft:
			AlignHTMLTagS = "<p align='left'>";
			break;
		case Qt::AlignRight:
			AlignHTMLTagS = "<p align='right'>";
			break;
		case Qt::AlignHCenter:
			AlignHTMLTagS = "<p align='center'>";
			break;
		default:
			break;
		}
	}
};