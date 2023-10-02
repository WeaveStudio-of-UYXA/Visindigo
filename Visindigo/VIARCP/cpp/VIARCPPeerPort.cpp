#include "../VIARCPPeerPort.h"

def_init VIARCPPeerPort::VIARCPPeerPort(bool enableListening, bool local, quint16 listenPort, VISuper* parent) :VIObject(parent) {
	if (enableListening) {
		Server = new QTcpServer(this);
		if (local) { Server->listen(QHostAddress::LocalHost, listenPort); }
		else { Server->listen(QHostAddress::Any, listenPort); }
		//上面有问题，可能发生端口冲突，需要处理
		connect(Server, &QTcpServer::newConnection, this, &VIARCPPeerPort::onNewConnection);
		setObjectName("Server " + QString::number(listenPort));
		setMaxConnectionCount(1);
	}
	else {
		setObjectName("Client");
	}
}
void VIARCPPeerPort::regRouter(VIARCPRemoteCallRouter* router) {
	if (router->FunctionName == "") { return; }
	if (Routers.contains(router->FunctionName)) {
		consoleLog(VIConsole::inWarningStyle("Peerport has already saved a routing object with function name :" + router->FunctionName));
		return;
	}
	Routers.insert(router->FunctionName, router);
}
VIARCPSocket* VIARCPPeerPort::connectToServer(QHostAddress host, quint16 port) {
	QTcpSocket* socket = new QTcpSocket(this);
	VIARCPSocket* handler = new VIARCPSocket(socket);
	connect(handler, &VIARCPSocket::remoteReturnDataPrepared, this, &VIARCPPeerPort::onRemoteReturnDataPrepared);
	connect(handler, &VIARCPSocket::remoteCallDataPrepared, this, &VIARCPPeerPort::onRemoteCallDataPrepared);
	Connections.append(handler);
	consoleLog("Connecting to " + host.toString() + ":" + QString::number(port));
	socket->connectToHost(host, port);
	handler->setObjectName(QString("%1:%2").arg(host.toString(), QString::number(port)));
	return handler;
}
void VIARCPPeerPort::doRemoterCall(VIARCPRemoteCaller* call) {
	if (call->Who == VI_NULL) {
		return;
	}
	if (!Connections.contains(call->Who)) {
		call->Who = VI_NULL;
		return;
	}
	RemoteCalls[call->Who].enqueue(call);
	sendRemoteCall(call->Call, call->Who);
}
void VIARCPPeerPort::setMaxConnectionCount(int count) {
	if (Server == VI_NULL) { return; }
	Server->setMaxPendingConnections(count);
}
void VIARCPPeerPort::sendRemoteCall(VIARCPCallDataObject& data, VIARCPSocket* handler) {
	handler->sendData(data);
}
void VIARCPPeerPort::onNewConnection() {
	consoleLog("New connection");
	QTcpSocket* socket = Server->nextPendingConnection();
	VIARCPSocket* handler = new VIARCPSocket(socket);
	handler->AsServer = true;
	connect(handler, &VIARCPSocket::remoteReturnDataPrepared, this, &VIARCPPeerPort::onRemoteReturnDataPrepared);
	connect(handler, &VIARCPSocket::remoteCallDataPrepared, this, &VIARCPPeerPort::onRemoteCallDataPrepared);
	connect(handler, &VIARCPSocket::disconnected, this, &VIARCPPeerPort::onDisconnected);
	Connections.append(handler);
}
void VIARCPPeerPort::onDisconnected(VIARCPSocket* handler) {
	Connections.removeOne(handler);
	if (handler->AsServer) {
		handler->deleteLater();
	}
}
void VIARCPPeerPort::onRemoteReturnDataPrepared(VIARCPSocket* handler, VIARCPReturnDataObject& data) {
	if (!RemoteCalls.contains(handler)) { return; }
	if (RemoteCalls[handler].isEmpty()) { return; }
	VIARCPRemoteCaller* call = RemoteCalls[handler].dequeue();
	call->preOnReturn(data);
}
void VIARCPPeerPort::onRemoteCallDataPrepared(VIARCPSocket* handler, VIARCPCallDataObject& data) {
	QString rCallName = data.getFunctionName();
	if (Routers.contains(rCallName)) {
		Routers[rCallName]->preOnRemoteCall(data, handler);
	}
	else {
		VIARCPReturnDataObject rtn;
		rtn.setStatusCode(VIARCPEnum::Status::UnknownFunction);
		handler->sendData(rtn);
	}
}