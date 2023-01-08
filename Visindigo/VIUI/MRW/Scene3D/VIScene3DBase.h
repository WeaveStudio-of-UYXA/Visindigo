#pragma once
#include "../../../Global.h"
#include <QtWidgets>
#include <QtCore>
#ifdef VI_USE_3D
#include <Qt3DCore>
#include <Qt3DExtras>
#include <QtQuickWidgets>
#endif
class VI3DWidget :public QWidget
{
	Q_OBJECT
#ifdef VI_USE_3D
public:
	QQuickWidget* QuickView;
	QWidget* Area3D;
	QGridLayout* CurrentLayout;
#endif
public:
	VI3DWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		//QuickView = new QQuickWidget(this);
		//CurrentLayout = new QGridLayout(this);
		//CurrentLayout->addWidget(QuickView);
		//CurrentLayout->setMargin(0);
		//QuickView->setResizeMode(QQuickWidget::ResizeMode::SizeViewToRootObject);
		//QuickView->setSource(QUrl("../../Visindigo/Visindigo/VI3D/NewFile.qml"));
	}

};