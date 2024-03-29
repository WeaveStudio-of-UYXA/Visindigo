﻿#pragma once
#include "../VICore/VIObject.h"
#include "private/VisindigoWidgetsPack.h"
#include "VIDynamicStyleSheet.h"
#include "VIWindowsTheme.h"
#include <QtWidgets>
#include <QtGui>
class VIPublicAPI VIUJWidgetBinder;

class VIPublicAPI VIAbstractWidget :public VIAbstractObject, public VITranslatableObject {
	_Public VIUJWidgetBinder* UJWidgetBinder = VI_NULLPTR;
	_Public QWidget* Self = VI_NULLPTR;
	_Public virtual void setTRHost(VITranslationSubHost* host) override final;
	_Public void setVIDStyleSheet(const QString& name, const QString& styleSheet);
	_Public void applyVIDSS(const QString& name);
	_Public QString getCurrentVIDSSName();
	_Public void refreshVIDStyleSheet();
	_Public void inheritParentTRHost();
};
typedef VIAbstractWidget VIBaseWidget;
#define VI_WIDGET_INIT \
	UJWidgetBinder = VI_NULLPTR;\
	Self = this;\
	inheritParentTRHost();\

#define VI_WIDGET VI_OBJECT;
class VIPublicAPI VIWidget :public QFrame, public VIBaseWidget {
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init VIWidget(QWidget* parent = VI_NULLPTR) :QFrame(parent) {
		if (parent == VI_NULLPTR) {
			this->setWindowTitle("Visindigo Widget");
		}
		VI_WIDGET_INIT;
	}
};
