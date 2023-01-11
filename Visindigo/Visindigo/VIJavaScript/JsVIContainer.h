#pragma once
#include "VIJSGlobal.h"
#include "JsVIBase.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

namespace JsVI {
	class VIContainer :public QObject
	{
		Q_OBJECT
	public:
		VIContainer(QObject* parent = Q_NULLPTR) :QObject(parent) {
		}
	};
}