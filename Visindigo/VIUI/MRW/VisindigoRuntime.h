#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "VIGUI2D.h"
#include "MRWGlobal.h"
#include "VIJSAPI/VIJSHost.h"

class VICentralWidget :public QWidget
{
	Q_OBJECT;
	_Public VI3DWidget* Widget3D;
	_Public VIGUI2DWidget* GUI2D;
	_Public QLabel* DebugInfoLabel;
	_Public def_init VICentralWidget(QWidget* parent) :QWidget(parent) {
		//Widget3D = new VI3DWidget(this);
		GUI2D = new VIGUI2DWidget(this);
		DebugInfoLabel = new QLabel(this);
		DebugInfoLabel->setObjectName("DebugInfo");
		DebugInfoLabel->setStyleSheet("QLabel#DebugInfo{font-size:30px;color:#0CDB23;font-family:'Microsoft YaHei'}");
		DebugInfoLabel->resize(300, 30);
		DebugInfoLabel->setText("MAX EPPS");
	}
	_Public void resizeEvent(QResizeEvent* event) {
		//Widget3D->resize(this->size());
		GUI2D->resize(this->size());
	}
	_Slot void setFrame(float frame) {
		DebugInfoLabel->setText(QString::number(frame, 'g', 9) + " EPPS");
	}
};

class VIRuntimeWindow :public QMainWindow
{
	Q_OBJECT;
	_Public VICentralWidget* CentralWidget;
	_Public QThread* JSHostThread;
	_Public VIJSHost* JSHost;
	_Public def_init VIRuntimeWindow(QWidget* parent = Q_NULLPTR) : QMainWindow(parent) {
		QPalette PAL;
		PAL.setColor(QPalette::Background, Qt::black);
		this->setPalette(PAL);
		gBEHAVIOR = new VIGeneralBehaviorHost(this);
		CentralWidget = new VICentralWidget(this);
		this->setCentralWidget(CentralWidget);
		JSHost = new VIJSHost(CentralWidget->GUI2D);
		JSHostThread = new QThread(this);
		JSHost->moveToThread(JSHostThread);
		JSHostThread->start();

		connect(JSHost, SIGNAL(initJSEngine(QJSEngine*)), this, SLOT(initJSEngine(QJSEngine*)), Qt::DirectConnection);
		BIND(JSHost->VIGUI2D, SIGNAL(SsetWindowTitle(QString)), this, SLOT(setWindowTitle(QString)));
		BIND(JSHost->VIGUI2D, SIGNAL(SsetStyleSheet(QString)), this, SLOT(setStyleSheet(QString)));
		BIND(JSHost->VIGUI2D, SIGNAL(SsetGeometry(int, int, int, int)), this, SLOT(setGeo(int, int, int, int)));
		BIND(JSHost->VIGUI2D, SIGNAL(Sresize(int, int)), this, SLOT(setSize(int, int)));
		BIND(JSHost->VIGUI2D, SIGNAL(SshowFullScreen()), this, SLOT(showFullScreen()));
		BIND(JSHost->VIGUI2D, SIGNAL(SenableGUIFrame()), this, SLOT(enableGUIFrame()));
		gBEHAVIOR->start();
		this->loadJS();
	}
	_Public void loadJS() {
#if DEPLOY == WINDOWS_DEPLOY
		JSHost->boot("../../Visindigo/Dev/test.js");
#elif DEPLOY == ANDROID_DEPLOY
		JSHost->boot("/sdcard/Visindigo/repos/Dev/test.js");
#endif
	}
	_Slot void setSize(int w, int h) {
#if VI_WINDOW == VI_WINDOW_SYS
		this->resize(w, h);
		move((QApplication::desktop()->screen()->width() - width()) / 2, (QApplication::desktop()->screen()->height() - height()) / 2);
#endif
	}
	_Slot void setGeo(int x, int y, int z, int w) {
#if VI_WINDOW == VI_WINDOW_SYS
		this->setGeometry(x, y, z, w);
#endif
	}
	_Slot void initJSEngine(QJSEngine* Engine) {
		PASS;
	}
	_Slot VIRuntimeWindow* getWin() {
		return this;
	}
	_Slot __Deprecated__("Use VISystem.print") void output(QString output) {
		qDebug() << output;
	}
	_Slot void enableGUIFrame() {
		//connect(Process, SIGNAL(currentFrame(float)), CentralWidget, SLOT(setFrame(float)), Qt::UniqueConnection);
	}
};
