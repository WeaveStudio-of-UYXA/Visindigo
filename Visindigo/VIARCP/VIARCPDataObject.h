#pragma once
#include "VIARCPBaseChunk.h"
#include "VIARCPTypeManager.h"
class VIARCPSocket;

class VIPublicAPI VIARCPAbstractDataObject
{
	friend class VIARCPSocket;
	_Protected VIARCPHeadChunk HEAD;
	_Protected QList<VIARCPDataChunk> DATA;
	_Protected virtual void clearChunks();
	_Public int getDataChunkLength();
	_Public void addDataChunk(VIARCPTypeManager::TypeName type, const QByteArray& data);
	_Public virtual void addDataChunk(const VIARCPDataChunk& data);
	_Public QList<VIARCPDataChunk>& getDataChunks();
	_Public VIARCPDataChunk getDataChunk(int index);
	_Public virtual QByteArray toByte() PureVirtual;
};

class VIPublicAPI VIARCPCallDataObject : public VIARCPAbstractDataObject
{
	friend class VIARCPSocket;
	_Private VIARCPCallChunk CALL;
	_Protected def_init VIARCPCallDataObject(const VIARCPHeadChunk& head, const VIARCPCallChunk& call, const QList<VIARCPDataChunk> data);
	_Public def_init VIARCPCallDataObject();
	_Public def_init VIARCPCallDataObject(const QString& functionName);
	_Public virtual void clearChunks() override;
	_Public virtual void addDataChunk(const VIARCPDataChunk& data) override;
	_Public void setFunctionName(const QString& functionName);
	_Public QString getFunctionName();
	_Public virtual QByteArray toByte() override;
};

class VIPublicAPI VIARCPReturnDataObject : public VIARCPAbstractDataObject
{
	friend class VIARCPSocket;
	_Private VIARCPRetnChunk RETN;
	_Protected def_init VIARCPReturnDataObject(const VIARCPHeadChunk& Head, const VIARCPRetnChunk& Retn, const QList<VIARCPDataChunk>& data);
	_Public def_init VIARCPReturnDataObject();
	_Public virtual void clearChunks() override;
	_Public virtual void addDataChunk(const VIARCPDataChunk& data) override;
	_Public void setStatusCode(VIARCPEnum::Status s);
	_Public VIARCPEnum::Status getStatusCode();
	_Public QByteArray toByte();
};
