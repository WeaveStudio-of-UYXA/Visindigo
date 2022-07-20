#pragma once
#include "../ah.h"
#include "../global_value.h"

class VIGUI :public QWidget 
{	
	Q_OBJECT
public:
	QPushButton* CheckButton;
	VIGUI(QWidget* parent = Q_NULLPTR) {
		this->setParent(parent);
		connect(Global::VServer, SIGNAL(receive(QString)), this, SLOT(print(QString)));
		Global::PyAPI->start();
		CheckButton = new QPushButton("检查链接", this);
		connect(CheckButton, SIGNAL(clicked()), this, SLOT(checkConnection()));
		qApp->focusWidget();
	}
public slots:
	void checkConnection() {
		Global::VServer->checkConnection();
	}
	void print(QString str) {
		qDebug() << str;
		if (str == "VI.VICore.getVisindigoVersion") {
			Global::VServer->Send("0.10.0");
		}
	}
			
};