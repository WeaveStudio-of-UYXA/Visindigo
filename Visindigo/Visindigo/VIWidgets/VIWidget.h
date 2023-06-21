#pragma once
#include "../VICore/VICore.h"
#include "VIWindowsTheme.h"
#include "VIStyleSheet.h"
#include <QtWidgets>
#include <QtGui>

class VIAbstractWidget :public VIAbstractObject {
	_Public VIStyleSheetManager* StyleSheetManager;
	_Public virtual void setStyleSheetPalette(VIColorPalette* palette) PureVirtual;
	_Public virtual void renewVTR() { onVTR(); }
	_Public virtual void VTR() HalfVirtual;
	_Public virtual void onVTR() PureVirtual;
};
typedef VIAbstractWidget VIBaseWidget;
#define VI_WIDGET_INIT \
	StyleSheetManager = new VIStyleSheetManager(this);

#define VI_WIDGET VI_OBJECT;\
_Public virtual void setStyleSheetPalette(VIColorPalette* palette) {\
	StyleSheetManager->setPalette(palette);\
	for (auto i = this->children().begin(); i != this->children().end(); i++) {\
		VIAbstractWidget* w = dynamic_cast<VIAbstractWidget*>(*i);\
		if (w != VI_NULLPTR) {\
			w->setStyleSheetPalette(palette);\
		}\
	}\
}\
_Public virtual void onVTR(){\
	VTR();\
	for (auto i = this->children().begin(); i != this->children().end(); i++) {\
		VIAbstractWidget* w = dynamic_cast<VIAbstractWidget*>(*i);\
		if (w != VI_NULLPTR) {\
			w->onVTR();\
		}\
	}\
}
class VIWidget :public QFrame, public VIBaseWidget {
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init VIWidget(QWidget* parent = VI_NULLPTR) :QFrame(parent) {
		if (parent == VI_NULLPTR) {
			this->setWindowTitle("Visindigo Widget");
		}
		VI_WIDGET_INIT;
	}
};

