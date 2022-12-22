#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "../../../Visindigo/VIObjects/VIObject/VIGlassObject.h"
#include "../../../VIJSAPI/VIJSGlobal.h"
namespace VIBase {
	class VIGUILabel :public VIGlassObject
	{
		Q_OBJECT;
		Public def_init VIGUILabel(QWidget* WidgetParent) {}
		Public def_del ~VIGUILabel() {}
		def_REF(setOpacityAni, float, float, int, bool);
		def_REF(setOpacity, float);
		def_REF(setGeometryPercent, float, float, float, float);
		def_REF(resizeEvent, QResizeEvent*);
		def_REF(setStyleSheet, QString);
		def_REF(setAlignment, Qt::AlignmentFlag);
		def_REF(movePercent, float, float);
		def_REF(resizePercent, float, float);
		def_REF(resizeWidthAndRatio, float, float);
		def_REF(moveCenter, float, float);
	};
}