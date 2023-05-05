#pragma once
#include "../macro/VI2DScene_m.h"
#include "../../VICore/VIAnimation.h"

class VI2DView;
class VI2DUnit :public QObject
{
	Q_OBJECT;
	friend class VI2DView;
	_Public VIOpacityAniBehavior* OpacityAni = new VIOpacityAniBehavior(this);
	_Public VIResizeAniBehavior* ResizeAni = new VIResizeAniBehavior(this);
	_Public QGraphicsItem* GraphicsItem = Q_NULLPTR;
	_Public def_init VI2DUnit(QObject* parent = Q_NULLPTR);
	_Public QRect RectangleInfo;
	_Public void setParentUnit(VI2DUnit* parent);
	_Public QGraphicsItem* getGraphicsItem();
	_Public ~VI2DUnit();
	_Public void setOpacity(float op);
	_Public void setOpacityAni(float opStart, float opEnd, VIMilliSecond duration);
	_Public void move(float px, float py);
	_Protected void __onSceneResize(QSize& size);
	_Public virtual void sceneResizeEvent(QSize& size) {};
	_Public QRect getGeometry();
};

class VI2DTextUnit :public VI2DUnit 
{
	Q_OBJECT;
	_Public QString AlignHTMLTagS = "<p align='left'>";
	_Public QString AlignHTMLTagE = "</p>";
	_Public VITextAniBehavior* TextAni;
	_Public QGraphicsTextItem* Item = new QGraphicsTextItem();
	_Public QFont TextFont;
	_Public bool TextSizeUsePercentage = false;
	_Public float TextSizePercentage;
	_Public def_init VI2DTextUnit(QObject* parent);
	_Public def_init VI2DTextUnit(VI2DUnit* parent);
	_Private void __init__();
	_Slot void setText(QString html);
	_Public void setTextAni(QString plainText, VIMilliSecond msPerChar, VIMilliSecond msWait);
	_Public void setTextAniContinue(QString plainText, VIMilliSecond msPerChar, VIMilliSecond msWait);
	_Public void setAlignment(Qt::AlignmentFlag align);
	_Public void setTextWidth(float width);
	_Public void setTextFont(QFont font);
	_Public void setTextColor(QColor color);
	_Public void setTextPixelSize(int px);
	_Public void setTextPixelPercentage(float percentage);
	_Public void setFontFamily(QString family);
	_Public void sceneResizeEvent(QSize size);
};

class VI2DFrameUnit :public VI2DTextUnit
{
	//_Private VIMainBehaviorHostDebug* DebugHost;
	_Public def_init VI2DFrameUnit(QObject* parent);
	_Public def_init VI2DFrameUnit(VI2DUnit* parent);
	_Private void __init__();
};
class VI2DPixmapUnit :public VI2DUnit
{
	Q_OBJECT;
	_Public QGraphicsPixmapItem* Item = new QGraphicsPixmapItem();
	_Public QSize PixmapSize;
	_Public def_init VI2DPixmapUnit(QObject* parent);
	_Public def_init VI2DPixmapUnit(VI2DUnit* parent);
	_Private void __init__();
	_Private void setPixmap(QPixmap& pixmap) {};
	_Public void sceneResizeEvent(QSize& size) {};
	_Public void setOffset(QSize& size) {};
};