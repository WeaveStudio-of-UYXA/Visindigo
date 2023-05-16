#pragma once
#include <QtCore>
#include <QtWidgets>
#include "../../Visindigo/VICore/VICore.h"

class YSPMainPack :public VIPackage
{
	QWidget* testWin;
	_Public def_init YSPMainPack(VISuper* parent = VI_NULLPTR) :VIPackage(parent) {
		PackageName = "YSPMainPack";
		testWin = new QWidget();
		testWin->setWindowTitle("YSPMainPack");
		testWin->show();
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
