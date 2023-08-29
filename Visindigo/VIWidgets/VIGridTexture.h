#pragma once
#include "../VICore/VICore.h"
#include "VIWidget.h"

class VIGridTextureAbstractDriver;
class VIGridTextureLabelBehavior;
class VIPublicAPI VIGridTexture :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIGridTextureLabelBehavior;
	friend class VIGridTextureAbstractDriver;
	VI_Property(QString, ConfigPath);
	_Private QList<QImage> Textures;
	_Private VIDocument::VIJSON json;
	_Private int Loop = 0;
	_Private int Fps = 32;
	_Protected bool Playing = false;
	_Public def_init VIGridTexture(VISuper* parent = VI_NULL);
	_Public bool load(const QString& configPath);
	_Public bool isPlaying();
	_Public const QImage& operator[](int index);
	_Public const QImage getImage(int index);
	_Public void appendImage(QImage image);
	_Public QSize getImageSize();
	_Public int getSize();
	_Public int getFps();
	_Public int getLoop();
	_Public void setFps(int fps);
	_Public void setLoop(int loop);
	_Public void save();
};

class VIPublicAPI VIGridTextureAbstractDriver :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Private VIGridTexture* GridTexture = VI_NULL;
	_Private int Index = 0;
	_Public def_init VIGridTextureAbstractDriver(QObject* parent = VI_NULL);
	_Public void setGridTexture(VIGridTexture* gridTexture);
	_Public void active(Visindigo::QuantifyTickType = Visindigo::T64) override;
	_Public void onActive() override;
	_Public void onTick() override;
	_Public void onSubside() override;
	_Public virtual void onImage(const QImage& image) PureVirtual;
};

class VIPublicAPI VIGridTextureLabelBehavior :public VIGridTextureAbstractDriver
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QLabel* Master = VI_NULL;
	_Public def_init VIGridTextureLabelBehavior(QLabel* parent = VI_NULL) :VIGridTextureAbstractDriver(parent) {
		Master = parent;
	};
	_Public void onImage(const QImage& image) override {
		Master->setPixmap(QPixmap::fromImage(image));
	}
};