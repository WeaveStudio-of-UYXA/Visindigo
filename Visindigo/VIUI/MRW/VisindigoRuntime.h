#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "VIGUI2D.h"
#include "MRWGlobal.h"
#include "../../VIJSAPI/VIJSHost.h"
class VI3DWidget :public QWidget
{
	Q_OBJECT
public:
	VI3DWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		qDebug() << "We hope there will be finished soon.";
	}
};
class VICentralWidget :public QWidget
{
	Q_OBJECT
public:
	VI3DWidget* Widget3D;
	VIGUI2DWidget* GUI2D;
	VIAnimationEventProcess* Process;
public:
	VICentralWidget(QWidget* parent,VIAnimationEventProcess* process) :QWidget(parent) {
		Process = process;
		Widget3D = new VI3DWidget(this);
		GUI2D = new VIGUI2DWidget(this, Process);
	}
	void resizeEvent(QResizeEvent* event) {
		GUI2D->resize(this->size());
		Widget3D->resize(this->size());
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
		
		
		Process = new VIAnimationEventProcess(this);
		
		CentralWidget = new VICentralWidget(this, Process);
		this->setCentralWidget(CentralWidget);
		JSHost = new VIJSHost(CentralWidget->GUI2D);
		JSHostThread = new QThread(this);
		JSHost->moveToThread(JSHostThread);
		JSHostThread->start();
		
		connect(JSHost, SIGNAL(initJSEngine(QJSEngine*)), this, SLOT(initJSEngine(QJSEngine*)), Qt::DirectConnection);
		connect(JSHost->GUIHost, SIGNAL(SsetWindowTitle(QString)), this, SLOT(setWindowTitle(QString)), Qt::BlockingQueuedConnection);
		connect(JSHost->GUIHost, SIGNAL(SshowFullScreen()), this, SLOT(showFullScreen()), Qt::BlockingQueuedConnection);
		Process->start();
		this->loadJS();
	}
	void loadJS() {
		JSHost->boot("../../Visindigo/Dev/test.js");
	}
public slots:
	void initJSEngine(QJSEngine* Engine) {
		//QJSValue VIRTWin = Engine->newQObject(this);
		//Engine->globalObject().setProperty("VIRTWin", VIRTWin);
	}
	VIRuntimeWindow* getWin() {
		return this;
	}
	void output(QString output) {
		qDebug() << output;
	}
};

