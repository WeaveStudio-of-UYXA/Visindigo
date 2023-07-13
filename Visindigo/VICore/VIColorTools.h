#pragma once
#include "VIObject.h"
#include <QtGui>

class VIColorTools :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_STATIC_CLASS (VIColorTools);
	_Public static QString toRGBString(const QColor& color) {
		return QString("rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue());
	}
	_Public static QString toRGBAString(const QColor& color) {
		return QString("rgba(%1,%2,%3,%4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
	}
	_Public static QColor reverseColor(const QColor& color) {
		return QColor(255 - color.red(), 255 - color.green(), 255 - color.blue(), color.alpha());
	}
	_Public static bool isLightColor(const QColor& color) {
		//Microsoft recommendation
		//see https://learn.microsoft.com/zh-cn/windows/apps/desktop/modernize/apply-windows-themes
		return (((5 * color.green()) + (2 * color.red()) + color.blue()) > (8 * 128));
	}
};
