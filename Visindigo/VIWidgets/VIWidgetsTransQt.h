#pragma once
#include "VIWidget.h"
#define VI_WIDGET_TRANS_QT(name) class VIPublicAPI VI##name :public Q##name, public VIBaseWidget {\
	Q_OBJECT;\
	VI_WIDGET;\
	_Public def_init VI##name(QWidget* parent = VI_NULLPTR) :Q##name(parent) {\
		VI_WIDGET_INIT;\
	}\
};

#define VI_WIDGET_TRANS_QTRAW(name) class VIPublicAPI VIQ##name :public Q##name, public VIBaseWidget {\
	Q_OBJECT;\
	VI_WIDGET;\
	_Public def_init VIQ##name(QWidget* parent = VI_NULLPTR) :Q##name(parent) {\
		VI_WIDGET_INIT;\
	}\
};

VI_WIDGET_TRANS_QT(Label);
VI_WIDGET_TRANS_QTRAW(Widget);
VI_WIDGET_TRANS_QT(PushButton);