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
		
		connect(MRWJSHost, SIGNAL(initJSEngine(QScriptEngine*)), this, SLOT(initJSEngine(QScriptEngine*)), Qt::DirectConnection);
		connect(MRWJSVIAPI, SIGNAL(SsetWindowTitle(QString)), this, SLOT(setWindowTitle(QString)), Qt::BlockingQueuedConnection);
		MRWAniProcess->start();
		//this->loadJS();
	}
	void loadJS() {
		QFile File;
		File.setFileName("../../Visindigo/Dev/test.js");
		File.open(QIODevice::ReadOnly);
		QTextStream Text(&File);
		Text.setCodec("UTF-8");
		QString String = Text.readAll();
		qDebug() << String;
		MRWJSHost->boot(String);
	}
public slots:
	void initJSEngine(QScriptEngine* Engine) {
		qDebug() << "INIT";
		QScriptValue VIRTWin = Engine->newQObject(this);
		Engine->globalObject().setProperty("VIRTWin", VIRTWin);
	}
	void output(QString output) {
		qDebug() << output;
	}
};

