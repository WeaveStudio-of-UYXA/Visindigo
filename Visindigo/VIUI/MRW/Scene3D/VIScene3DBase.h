#pragma once
#include <Qt3DCore>
#include <Qt3DExtras>
#include <QtWidgets>
#include <QtCore>
#include <QtQuickWidgets>

class VI3DWidget :public QWidget
{
	Q_OBJECT
public:
	QQuickWidget* QuickView;
	QWidget* Area3D;
	QGridLayout* CurrentLayout;
	VI3DWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		//QuickView = new QQuickWidget(this);
		//CurrentLayout = new QGridLayout(this);
		//CurrentLayout->addWidget(QuickView);
		//CurrentLayout->setMargin(0);
		//QuickView->setResizeMode(QQuickWidget::ResizeMode::SizeViewToRootObject);
		//QuickView->setSource(QUrl("../../Visindigo/Visindigo/VI3D/NewFile.qml"));
	}
};