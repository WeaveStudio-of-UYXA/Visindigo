#pragma once
#include "VIARCPPackageMeta.h"
#include "VIARCPDataObject.h"
#include "VIARCPTypeManager.h"
#include <QtNetwork>
class VIARCPPeerPort;
class VIARCPRemoteCallRouter;
class VIPublicAPI VIARCPSocket :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIARCPPeerPort;
	friend class VIARCPRemoteCallRouter;
	_Signal void connected(VIARCPSocket* connection);
	_Signal void remoteReturnDataPrepared(VIARCPSocket* connection, VIARCPReturnDataObject& obj);
	_Signal void remoteCallDataPrepared(VIARCPSocket* connection, VIARCPCallDataObject& obj);
	_Signal void disconnected(VIARCPSocket* connection);
	_Private QByteArray Cache;
	_Private VIARCPHeadChunk Head;
	_Private VIARCPCallChunk Call;
	_Private VIARCPRetnChunk Retn;
	_Private bool GetCallOrRetn = false;
	_Private quint32 ParaCount = 0;
	_Private QList<VIARCPDataChunk> DataChunkList;
	_Public QTcpSocket* Socket;
	_Private QString RandomString;
	_Protected bool AsServer = false;
	_Private quint8 maxReconnect = 5;
	_Private quint8 reconnectCount = 0;
	_Private VIARCPEnum::Status ClienStatus = VIARCPEnum::Status::Success;
	_Public def_init VIARCPSocket(QTcpSocket* s);
	_Public static QString getRandomString(int length = 32);
	_Public void reConnect();
	_Public void setMaxReconnectCount(quint8 count);
	_Private void setTcpSocket(QTcpSocket* s);
	_Public void onConnected();
	_Private void onDisconnected();
	_Private void onErrorOccurred(QAbstractSocket::SocketError error);
	_Public void sendData(VIARCPCallDataObject& obj);
	_Protected void sendData(VIARCPReturnDataObject& obj);
	_Private void handleData();
	_Private void handleCache();
	_Private VIARCPEnum::Status onChunkData(const VIARCPDataChunk& chunk);
	_Private void debugOutput(VIARCPCallDataObject& obj, bool get);
	_Private void debugOutput(VIARCPReturnDataObject& obj, bool get);
};