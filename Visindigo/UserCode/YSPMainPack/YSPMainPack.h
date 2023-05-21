#pragma once
#include <QtCore>
#include <QtWidgets>
#include "../../Visindigo/VICore/VICore.h"
#include "../../Visindigo/VI2DScene/VI2DSceneWidget.h"

class RotationBehavior :public VIBasicBehavior {
	Q_OBJECT;
	VI_Property(VI2DSceneWidget*, Scene);
	_Public def_init RotationBehavior(QObject* parent = VI_NULLPTR) :VIBasicBehavior(parent) {};
	_Public virtual void onActive() HalfVirtual;
	_Public virtual void onTick() {
		Scene->TestProxy->setRotation(Scene->TestProxy->rotation() + 2);
		Scene->TestLabel->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
	};
	_Public virtual void onPassive() HalfVirtual;
};
class YSPMainPack :public VIPackage
{
	Q_OBJECT;
	QWidget* testWin;
	VIDebugBehavior* debugBehavior;
	VI2DSceneWidget* scene;
	RotationBehavior* rotationBehavior;
	_Public def_init YSPMainPack(QObject* parent = VI_NULLPTR) :VIPackage(parent) {
		PackageName = "YSPMainPack";
		testWin = new QWidget();
		testWin->setWindowTitle("YSPMainPack");
		testWin->show();
		debugBehavior = new VIDebugBehavior(this);
		debugBehavior->active(VIAbstractBehavior::QuantifyTickType::T20);
		scene = new VI2DSceneWidget(testWin);
		scene->setGeometry(0, 0, 800, 600);
		scene->show();
		rotationBehavior = new RotationBehavior(this);
		rotationBehavior->setScene(scene);
		rotationBehavior->active(VIAbstractBehavior::QuantifyTickType::T128);
	};
	_Public virtual void onActive() {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is active!");
	};
	_Public virtual void onPassive() {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is passive!");
	};
	_Public virtual void onTick() {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is ticking!");
	};
	_Public virtual void onEvent(QEvent* e) {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is eventing!");
	};
};
