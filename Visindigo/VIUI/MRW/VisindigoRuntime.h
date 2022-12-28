#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "VIGUI2D.h"
#include "MRWGlobal.h"
#include "VIJSAPI/VIJSHost.h"

class VICentralWidget :public QWidget
{
	Q_OBJECT
public:
	VI3DWidget* Widget3D;
	VIGUI2DWidget* GUI2D;
	VIAnimationEventProcess* Process;
	QLabel* DebugInfoLabel;
public:
	VICentralWidget(QWidget* parent, VIAnimationEventProcess* process) :QWidget(parent) {
		Process = process;
		//Widget3D = new VI3DWidget(this);
		GUI2D = new VIGUI2DWidget(this, Process);
		DebugInfoLabel = new QLabel(this);
		DebugInfoLabel->setObjectName("DebugInfo");
		DebugInfoLabel->setStyleSheet("QLabel#DebugInfo{font-size:30px;color:#0CDB23;font-family:'Microsoft YaHei'}");
		DebugInfoLabel->resize(300, 30);
		DebugInfoLabel->setText("MAX EPPS");
	}
	void resizeEvent(QResizeEvent* event) {
		//Widget3D->resize(this->size());
		GUI2D->resize(this->size());
	}
public slots:
	void setFrame(float frame) {
		DebugInfoLabel->setText(QString::number(frame, 'g', 9) + " EPPS");
	}
};

class VIRuntimeWindow :public QMainWindow
{
	Q_OBJECT
public:
	VICentralWidget* CentralWidget;
	QThread* JSHostThread;
	VIJSHost* JSHost;
	VIAnimationEventProcess* Process;
	VIRuntimeWindow(QWidget* parent = Q_NULLPTR) : QMainWindow(parent) {
		QPalette PAL;
		PAL.setColor(QPalette::Background, Qt::black);
		this->setPalette(PAL);
		gBEHAVIOR = new VIGeneralBehaviorHost(this);
		Process = new VIAnimationEventProcess(this);
		CentralWidget = new VICentralWidget(this, Process);
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
		Process->start();
		gBEHAVIOR->start();
		this->loadJS();
	}
	void loadJS() {
		JSHost->boot("../../Visindigo/Dev/test.js");
	}
public slots:
	void setSize(int w, int h) {
		this->resize(w, h);
		move((QApplication::desktop()->screen()->width() - width()) / 2, (QApplication::desktop()->screen()->height() - height()) / 2);
	}
	void setGeo(int x, int y, int z, int w) {
		this->setGeometry(x, y, z, w);
	}
	void initJSEngine(QJSEngine* Engine) {
	}
	VIRuntimeWindow* getWin() {
		return this;
	}
	void output(QString output) {
		qDebug() << output;
	}
	void enableGUIFrame() {
		connect(Process, SIGNAL(currentFrame(float)), CentralWidget, SLOT(setFrame(float)), Qt::UniqueConnection);
	}
};
