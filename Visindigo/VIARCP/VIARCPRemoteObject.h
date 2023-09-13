#pragma once
#include "VIARCPSocket.h"
class VIARCPPeerPort;

class VIPublicAPI VIARCPRemoteCallRouter :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QList<VIARCPTypeManager::TypeName> TypeNames;
	_Public VIARCPSocket* Who = VI_NULL;
	_Private VIARCPReturnDataObject RET;
	_Public QString FunctionName;
	_Public virtual void onRemoteCall(QList<VIARCPDataChunk>& params, VIARCPSocket* who) PureVirtual;
	_Public void preOnRemoteCall(VIARCPCallDataObject& obj, VIARCPSocket* who);
	_Public void setStatusCode(VIARCPEnum::Status code);
	_Public void addReturnData(VIARCPDataChunk& data);
};

class VIPublicAPI VIARCPRemoteCaller :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public VIARCPSocket* Who = VI_NULL;
	_Public VIARCPCallDataObject Call;
	_Public QList<VIARCPTypeManager::TypeName> TypeNames;
	_Public VIARCPPeerPort* Port = VI_NULL;
	_Public void setFunctionName(QString name);
	_Public void addDataChunk(VIARCPDataChunk& data);
	_Public void setWho(VIARCPSocket* who);
	_Public void setPort(VIARCPPeerPort* port);
	_Public void doRemoteCall();
	_Public void preOnReturn(VIARCPReturnDataObject& obj);
	_Public virtual void onReturn(QList<VIARCPDataChunk>& obj) PureVirtual;
};