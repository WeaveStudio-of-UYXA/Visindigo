#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "VIGUI2D.h"
#include "MRWGlobal.h"
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
public:
	VICentralWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		Widget3D = new VI3DWidget(this);
		GUI2D = new VIGUI2DWidget(this);
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
	VIRuntimeWindow(QWidget* parent = Q_NULLPTR) : QMainWindow(parent) {
		
		QPalette PAL;
		PAL.setColor(QPalette::Background, Qt::black);
		this->setPalette(PAL);
		CentralWidget = new VICentralWidget(this);
		this->setCentralWidget(CentralWidget);
		
		MRWGlobal::Process = new VIAnimationEventProcess(this);
		MRWGlobal::JSHost = new VIJSHost();
		JSHostThread = new QThread(this);
		MRWJSHost->moveToThread(JSHostThread);
		JSHostThread->start();
		
		connect(MRWJSHost, SIGNAL(initJSEngine(QJSEngine*)), this, SLOT(initJSEngine(QJSEngine*)), Qt::DirectConnection);
		connect(MRWJSVIAPI, SIGNAL(SsetWindowTitle(QString)), this, SLOT(setWindowTitle(QString)), Qt::BlockingQueuedConnection);
		MRWAniProcess->start();
		this->loadJS();
	}
	void loadJS() {
		MRWJSHost->boot("../../Visindigo/Dev/test.js");
	}
public slots:
	void initJSEngine(QJSEngine* Engine) {
		qDebug() << "INIT";
		QJSValue VIRTWin = Engine->newQObject(this);
		Engine->globalObject().setProperty("VIRTWin", VIRTWin);
	}
	VIRuntimeWindow* getWin() {
		return this;
	}
	void output(QString output) {
		qDebug() << output;
	}
};

