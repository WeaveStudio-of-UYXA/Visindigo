#pragma once
#include "../ah.h"

class VIServer :public QObject
{
	Q_OBJECT
signals:
	void receive(QString);
private:
	QTcpServer* Server;
	QTcpSocket* Client;
	QString Cache="";
public:
	VIServer(QObject *parent = Q_NULLPTR) {
		this->setParent(parent);
		Server = new QTcpServer(this);
		connect(Server, SIGNAL(newConnection()), this, SLOT(getConnection()));
		Server->listen(QHostAddress::Any, 54179);		
	}
public slots:
	void checkConnection() {
		qDebug()<< "Has pending connections:"<<Server->hasPendingConnections();
		qDebug() << Server->serverAddress();
		qDebug() << Server->serverPort();
		qDebug() << "Is listening:" << Server->isListening();
	}
	void getConnection() {
		qDebug() << "VI:服务端接受通讯";
		Client = Server->nextPendingConnection();
		connect(Client, SIGNAL(readyRead()), this, SLOT(Receive()));
		connect(Client, SIGNAL(disconnected()), this, SLOT(disconnected()));
	}
	void Receive() {
		//qDebug() << "reciveMessage";
		Cache += Client->readAll();
		QStringList CacheList = Cache.split("\n");
		//qDebug() << CacheList;
		int Length = CacheList.length();
		if (CacheList.last() == "") {
			for (int i = 0; i < Length - 1; i++) {
				emit receive(CacheList[i]);
			}
		}
		else {
			for (int i = 0; i < Length; i++) {
				emit receive(CacheList[i]);
			}
		}
		Cache = CacheList.last();
	}
	void disconnected() {
		Client->close();
		qDebug() << "VI:断开与PyVI的链接";
		if (Cache != "") { emit receive(Cache); Cache = ""; }
	}
	void Send(QString str) {
		Client->write(str.toUtf8());
	}
};