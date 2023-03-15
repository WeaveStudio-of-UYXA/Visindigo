#include "VI2DUnit.h"

/*
* =====================================
* VI2DUnit
* =====================================
*/
def_init VI2DUnit::VI2DUnit(QObject* parent) :QObject(parent) {}
void VI2DUnit::setParentUnit(VI2DUnit* parent) {
	GraphicsItem->setParentItem(parent->GraphicsItem);
	OpacityAni->setHost(mBEHAVIOR);
}
QGraphicsItem* VI2DUnit::getGraphicsItem() {
	return GraphicsItem;
}
def_del VI2DUnit::~VI2DUnit() {
	if (GraphicsItem != Q_NULLPTR) {
		delete GraphicsItem;
	}
}
void VI2DUnit::setOpacity(float op) {
	this->GraphicsItem->setOpacity(op);
}
void VI2DUnit::setOpacityAni(float opStart, float opEnd, VIMilliSecond duration) {
	OpacityAni->setOpacity(opStart, opEnd, duration);
	OpacityAni->active();
}
void VI2DUnit::__onSceneResize(QSize& size) {
	this->sceneResizeEvent(size);
	QList<QObject*> children = this->children();
	for (auto i = children.begin(); i != children.end(); i++) {
		VI2DUnit* child = dynamic_cast<VI2DUnit*>(*i);
		if (child != Q_NULLPTR) {
			child->__onSceneResize(size);
		}
	}
}
void VI2DUnit::move(float px, float py) {
	GraphicsItem->setPos(px, py);
	RectangleInfo.setX(px);
	RectangleInfo.setY(py);
}
QRect VI2DUnit::getGeometry() {
	return GraphicsItem->boundingRect().toRect();
}

/*
* =====================================
* VI2DTextUnit :public VI2DUnit
* =====================================
*/
def_init VI2DTextUnit::VI2DTextUnit(QObject* parent) :VI2DUnit(parent) {
	this->__init__();
}
def_init VI2DTextUnit::VI2DTextUnit(VI2DUnit* parent) : VI2DUnit(parent) {
	this->__init__();
	Item->setParentItem(parent->GraphicsItem);
}
void VI2DTextUnit::__init__() {
	GraphicsItem = Item;
	TextFont.setFamily("Microsoft YaHei");
	TextFont.setPixelSize(20);
	Item->setFont(TextFont);
	TextAni = new VITextAniBehavior(this);
	TextAni->setHost(mBEHAVIOR);
	connect(TextAni, SIGNAL(getText(QString)), this, SLOT(setText(QString)));
}
void VI2DTextUnit::setText(QString html) {
	Item->setHtml(AlignHTMLTagS + html + AlignHTMLTagE);
	//Item->adjustSize();
}
void VI2DTextUnit::setTextAni(QString plainText, VIMilliSecond msPerChar, VIMilliSecond msWait) {
	TextAni->setTextAni(plainText, msPerChar, msWait, false);
	TextAni->active();
}
void VI2DTextUnit::setTextAniContinue(QString plainText, VIMilliSecond msPerChar, VIMilliSecond msWait) {
	TextAni->setTextAni(plainText, msPerChar, msWait, true);
	TextAni->active();
}
void VI2DTextUnit::setAlignment(Qt::AlignmentFlag align) {
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
void VI2DTextUnit::setTextWidth(float width) {
	this->Item->setTextWidth(width);
}
void VI2DTextUnit::setTextFont(QFont font) {
	this->TextFont = font;
	this->Item->setFont(font);
}
void VI2DTextUnit::setTextColor(QColor color) {
	this->Item->setDefaultTextColor(color);
}
void VI2DTextUnit::setTextPixelSize(int px) {
	this->TextSizeUsePercentage = false;
	this->TextFont.setPixelSize(px);
	this->Item->setFont(TextFont);
}
void VI2DTextUnit::setTextPixelPercentage(float percentage) {
	this->TextSizeUsePercentage = true;
	this->TextSizePercentage = percentage;
	this->TextFont.setPixelSize(this->getGeometry().height() * percentage);
	this->Item->setFont(TextFont);
}
void VI2DTextUnit::setFontFamily(QString family) {
	this->TextFont.setFamily(family);
	this->Item->setFont(TextFont);
}
void VI2DTextUnit::sceneResizeEvent(QSize size) {
	if (TextSizeUsePercentage) {
		this->TextFont.setPixelSize(size.height() * TextSizePercentage);
		this->Item->setFont(TextFont);
	}
}
def_init VI2DFrameUnit::VI2DFrameUnit(QObject* parent) :VI2DTextUnit(parent) {
	this->__init__();
}
def_init VI2DFrameUnit::VI2DFrameUnit(VI2DUnit* parent) : VI2DTextUnit(parent) {
	this->__init__();
	Item->setParentItem(parent->GraphicsItem);
}
void VI2DFrameUnit::__init__() {
	GraphicsItem = Item;
	TextFont.setFamily("Microsoft YaHei");
	TextFont.setPixelSize(20);
	Item->setFont(TextFont);
	DebugHost = new VIMainBehaviorHostDebug();
	DebugHost->setHost(mBEHAVIOR);
	DebugHost->active();
	connect(DebugHost, &VIMainBehaviorHostDebug::getHostSpeed, [this](unsigned int s) {this->setText(QString::number(s)); });
}
/*
* =====================================
* VI2DPixmapUnit :public VI2DUnit
* =====================================
*/
def_init VI2DPixmapUnit::VI2DPixmapUnit(QObject* parent) :VI2DUnit(parent) {
	this->__init__();
}
def_init VI2DPixmapUnit::VI2DPixmapUnit(VI2DUnit* parent) : VI2DUnit(parent) {
	this->__init__();
	Item->setParentItem(parent->GraphicsItem);
}
void VI2DPixmapUnit::__init__() {
	GraphicsItem = Item;
}

