#pragma once
#include "../VICore/VICore.h"
#include <QtWidgets>
class VI2DSceneAnimationBehavior :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Property(QGraphicsItem*, Target);
	_Public def_init VI2DSceneAnimationBehavior(VISuper* parent = VI_NULLPTR) :VIAnimationBehavior(parent) {}
};

class VI2DSceneRotateAnimationBehavior :public VI2DSceneAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init VI2DSceneRotateAnimationBehavior(VISuper* parent = VI_NULLPTR) :VI2DSceneAnimationBehavior(parent) {}
	_Public void onActive() {
	}
	_Public void onTick() {
	}
	_Public void onSubside() {
	}
};