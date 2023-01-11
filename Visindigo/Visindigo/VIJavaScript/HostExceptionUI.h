#pragma once
#include <QtQml>
#include "VIJSGlobal.h"
#include "../../VIUI/MRW/GUI2D/VI2DGUI.h"
#include "..//VICore/VIGuiAnimation.h"
#include "../../VIUI/MRW/VIGUI2D.h"
#include "../../Global.h"

class JSVIExceptionLabel :public VI2DGUILabel
{
	Q_OBJECT
public:
	JSVIExceptionLabel(QWidget* WidgetParent) :VI2DGUILabel(WidgetParent) {
	}
};