#pragma once
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "GUI2D/VI2DGUI.h"
#include "MRWGlobal.h"
class VIGUI2DWidget :public QWidget
{
	Q_OBJECT
public:
	VIGUI2DWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		
	}
};
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
	VICentralWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		qDebug() << "We hope there will be finished soon.";
	}
};

class VIRuntimeWindow :public QMainWindow
{
	Q_OBJECT
public:
	VICentralWidget* CentralWidget;
	QThread* JSHostThread;
	VIRuntimeWindow(QWidget* parent = Q_NULLPTR) : QMainWindow(parent) {
		MRWGlobal::Process = new VIAnimationEventProcess(this);
		MRWGlobal::JSHost = new VIJSHost();
		JSHostThread = new QThread(this);
		MRWJSHost->moveToThread(JSHostThread);
		JSHostThread->start();
		CentralWidget = new VICentralWidget(this);
		this->setCentralWidget(CentralWidget);
		connect(MRWJSHost, SIGNAL(initJSEngine(QScriptEngine*)), this, SLOT(initJSEngine(QScriptEngine*)), Qt::DirectConnection);
		MRWAniProcess->start();
		this->loadJS();
	}
	void loadJS() {
		MRWJSHost->boot("function main() {VIRTWin.output(\"Hello World!\");}");
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

