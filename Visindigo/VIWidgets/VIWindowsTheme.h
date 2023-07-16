#pragma once
#include "../VICore/VIObject.h"
#include "../VICore/VIMultiPlatform.h"
#include <QtWidgets>

#ifdef WINDOWS_DEPLOY
#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib,"Dwmapi.lib")
#endif

class VIPublicAPI VIWindowsTheme :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
#ifdef WINDOWS_DEPLOY
	_Public static QColor getWindowsThemeColor() {
		DWORD crColorization;
		BOOL fOpaqueBlend;
		DWORD theme_color{};
		HRESULT result = DwmGetColorizationColor(&crColorization, &fOpaqueBlend);

		BYTE r = 0, g = 0, b = 0;
		if (result == S_OK)
		{
			r = (crColorization >> 16) % 256;
			g = (crColorization >> 8) % 256;
			b = crColorization % 256;
			theme_color = RGB(r, g, b);
		}
		//qDebug()<<r<<g<<b;
		QColor color(r, g, b);
		return color;
	}
#else
	_Public static QColor getWindowsThemeColor() {
		return VIMultiPlatform::getSystemThemeColor();
	}
#endif
};