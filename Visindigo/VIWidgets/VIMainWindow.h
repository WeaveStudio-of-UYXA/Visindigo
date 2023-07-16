#pragma once
#include "VIWidget.h"



class VIPublicAPI VIMainWindow : public VIWidget {
	Q_OBJECT;
	VI_OBJECT;
	_Signal void windowColorChanged(QColor color);
	_Public VIColorPalette* WindowPalette;
	_Private private_VIColorChangeAnimationBehavior* colorChangeAnimationBehavior;
	_Public def_init VIMainWindow(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		this->setWindowTitle("Visindigo Main Window");
		WindowPalette = new VIColorPalette(this);
		WindowPalette->createPalette("default");
		WindowPalette->addColorWithNameTo("SystemThemeColor", VIWindowsTheme::getWindowsThemeColor(), "default");
		//qDebug()<< VIWindowsTheme::getWindowsThemeColor();
		colorChangeAnimationBehavior = new private_VIColorChangeAnimationBehavior(this);
		colorChangeAnimationBehavior->setPalette(WindowPalette);
		colorChangeAnimationBehavior->setColorName("SystemThemeColor");
		colorChangeAnimationBehavior->setPaletteName("default");
	}
	_Public VIColorPalette* getWindowPalette() {
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
			//qDebug() << "WM_SYSCOLORCHANGE";
			return true;
		}
#endif
		return false;
	}
};