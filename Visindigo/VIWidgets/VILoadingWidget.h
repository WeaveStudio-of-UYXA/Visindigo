#pragma once
#include "VIWidget.h"

class VIPublicAPI VILoadingWidget :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	VI_ProtectedProperty(float, Progress);
	_Protected
		_Public def_init VILoadingWidget(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
	}
	_Slot void updateProgress(float progress) {
		setProgress(progress);
	}
};