#pragma once
#include "../VICore/VICore.h"
#include "VIWindowsTheme.h"
#include "VIStyleSheet.h"
#include <QtWidgets>
#include <QtGui>

class VIWidget :public QFrame, public VIBaseObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public VIStyleSheetManager* StyleSheetManager;
	_Public def_init VIWidget(QWidget* parent = VI_NULLPTR) :QFrame(parent) {
		if (parent == VI_NULLPTR) {
			this->setWindowTitle("Visindigo Widget");
		}
		StyleSheetManager = new VIStyleSheetManager(this);
	}
	_Public virtual void setStyleSheetPalette(VIStyleSheetPalette* palette) {
		StyleSheetManager->setPalette(palette);
		for (auto& child : this->findChildren<VIWidget*>()) {
			consoleLog("Find Child" + child->getClassName());
			child->setStyleSheetPalette(palette);
		}
	}
};

class VIMainWindow : public VIWidget {
	Q_OBJECT;
	VI_OBJECT;
	_Signal void windowColorChanged(QColor color);
	_Public VIStyleSheetPalette* WindowPalette;
	_Private private_VIColorChangeAnimationBehavior* colorChangeAnimationBehavior;
	_Public def_init VIMainWindow(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		this->setWindowTitle("Visindigo Main Window");
		WindowPalette = new VIStyleSheetPalette(this);
		WindowPalette->createPalette("default");
		WindowPalette->addColorWithNameTo("SystemThemeColor", VIWindowsTheme::getWindowsThemeColor(), "default");
		qDebug()<< VIWindowsTheme::getWindowsThemeColor();
		colorChangeAnimationBehavior = new private_VIColorChangeAnimationBehavior(this);
		colorChangeAnimationBehavior->setPalette(WindowPalette);
		colorChangeAnimationBehavior->setColorName("SystemThemeColor");
		colorChangeAnimationBehavior->setPaletteName("default");
	}
	_Public VIStyleSheetPalette* getWindowPalette() {
		return WindowPalette;
	}
	_Protected bool nativeEvent(const QByteArray& eventType, void* message, long* result) override {
#ifdef WINDOWS_DEPLOY
		MSG* msg = (MSG*)message;
		switch (msg->message)
		{
		case WM_DWMCOLORIZATIONCOLORCHANGED:
			colorChangeAnimationBehavior->setTargetColor(VIWindowsTheme::getWindowsThemeColor());
			colorChangeAnimationBehavior->setDuration(1000);
			colorChangeAnimationBehavior->active();
			emit windowColorChanged(VIWindowsTheme::getWindowsThemeColor());
			return true;
		case WM_SYSCOLORCHANGE:
			qDebug() << "WM_SYSCOLORCHANGE";
			return true;
		}
#endif
		return false;
	}
};