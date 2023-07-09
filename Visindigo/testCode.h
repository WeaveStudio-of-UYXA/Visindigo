#pragma once
#include "VICore/VICore.h"
#include "VIWidgets/VIWidgets.h"

class BinderTest :public VIUJWidgetBinder
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init BinderTest(VISuper* parent = VI_NULLPTR) :VIUJWidgetBinder(parent) {
		setTargetInstanceName("Root.Subwidget.Label_1");
	}
	_Public virtual bool enterEvent(QEvent* event)override {
		qDebug() << "Enter";
		self->setStyleSheet("VILabel{background-color: rgb(255, 0, 0);}");
		return true;
	}
	_Public virtual bool leaveEvent(QEvent* event)override {
		qDebug() << "Leave";
		self->setStyleSheet("VILabel{background-color: rgb(0, 255, 0);}");
		return true;
	}
};