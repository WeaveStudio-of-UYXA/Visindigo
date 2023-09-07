#pragma once
#include "VIARCPSocket.h"
#include "VIARCPRemoteObject.h"

class VIPublicAPI VIARCPPeerPort :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QTcpServer* Server = VI_NULL;
	_Public QList<VIARCPSocket*> Connections;
	_Public QMap<QString, VIARCPRemoteCallRouter*> Routers;
	_Public QMap<VIARCPSocket*, QQueue<VIARCPRemoteCaller*>> RemoteCalls;
	_Public def_init VIARCPPeerPort(bool enableListening = true, bool local = true, quint16 listenPort = 11450, VISuper* parent = VI_NULL);
	_Public void regRouter(VIARCPRemoteCallRouter* router);
	_Public VIARCPSocket* connectToServer(QHostAddress host, quint16 port);
	_Public void doRemoterCall(VIARCPRemoteCaller* call);
	_Public void setMaxConnectionCount(int count);
	_Private void sendRemoteCall(VIARCPCallDataObject& data, VIARCPSocket* handler);
	_Private void onNewConnection();
	_Private void onDisconnected(VIARCPSocket* handler);
	_Private void onRemoteReturnDataPrepared(VIARCPSocket* handler, VIARCPReturnDataObject& data);
	_Private void onRemoteCallDataPrepared(VIARCPSocket* handler, VIARCPCallDataObject& data);
};