#include "../VIARCPDataObject.h"

void VIARCPAbstractDataObject::clearChunks() {
	DATA.clear();
}
int VIARCPAbstractDataObject::getDataChunkLength() {
	return DATA.size();
}
void VIARCPAbstractDataObject::addDataChunk(VIARCPTypeManager::TypeName type, const QByteArray& data) {
	VIARCPDataChunk chunk;
	QByteArray typeNameArray = VIARCPTypeManager::getTypeNameString(type).toUtf8();
	chunk.TypeNameLength = typeNameArray.size();
	chunk.DataLength = data.size();
	chunk.AllData = data+typeNameArray;
	addDataChunk(chunk);
}
void VIARCPAbstractDataObject::addDataChunk(const VIARCPDataChunk& data) {
	DATA.append(data);
}
QList<VIARCPDataChunk>& VIARCPAbstractDataObject::getDataChunks() {
	return DATA;
}
VIARCPDataChunk VIARCPAbstractDataObject::getDataChunk(int index) {
	return DATA[index];
}
def_init VIARCPCallDataObject::VIARCPCallDataObject(const VIARCPHeadChunk& head, const VIARCPCallChunk& call, const QList<VIARCPDataChunk> data) {
	HEAD = head;
	CALL = call;
	DATA = data;
}
def_init VIARCPCallDataObject::VIARCPCallDataObject() {}
def_init VIARCPCallDataObject::VIARCPCallDataObject(const QString& functionName) {
	setFunctionName(functionName);
}
void VIARCPCallDataObject::clearChunks() {
	VIARCPAbstractDataObject::clearChunks();
	CALL.ParaCount = 0;
}
void VIARCPCallDataObject::addDataChunk(const VIARCPDataChunk& data) {
	VIARCPAbstractDataObject::addDataChunk(data);
	CALL.ParaCount = DATA.size();
}
void VIARCPCallDataObject::setFunctionName(const QString& functionName) {
	CALL.FunctionName = functionName.toUtf8();
	CALL.FunctionNameLength = functionName.size();
}
QString VIARCPCallDataObject::getFunctionName() {
	return QString::fromUtf8(CALL.FunctionName);
}
QByteArray VIARCPCallDataObject::toByte() {
	QByteArray rtn;
	rtn.append((char*)&HEAD, sizeof(VIARCPHeadChunk));
	rtn.append((char*)&CALL, sizeof(VIARCPCallChunk) - sizeof(QByteArray));
	rtn.append(CALL.FunctionName);
	for (auto i : DATA) {
		rtn.append((char*)&i, sizeof(VIARCPDataChunk) - sizeof(QByteArray));
		rtn.append(i.AllData);
	}
	return rtn;
}

def_init VIARCPReturnDataObject::VIARCPReturnDataObject(const VIARCPHeadChunk& Head, const VIARCPRetnChunk& Retn, const QList<VIARCPDataChunk>& data) {
	HEAD = Head;
	RETN = Retn;
	DATA = data;
}
def_init VIARCPReturnDataObject::VIARCPReturnDataObject() {
	PASS;
}
void VIARCPReturnDataObject::clearChunks() {
	VIARCPAbstractDataObject::clearChunks();
	RETN.ParaCount = 0;
	RETN.StatusCode = (quint16)VIARCPEnum::Status::Success;
}
void VIARCPReturnDataObject::addDataChunk(const VIARCPDataChunk& data) {
	VIARCPAbstractDataObject::addDataChunk(data);
	RETN.ParaCount = DATA.size();
}
void VIARCPReturnDataObject::setStatusCode(VIARCPEnum::Status s) {
	RETN.StatusCode = (quint16)s;
}
VIARCPEnum::Status VIARCPReturnDataObject::getStatusCode() {
	return (VIARCPEnum::Status)RETN.StatusCode;
}

QByteArray VIARCPReturnDataObject::toByte() {
	QByteArray rtn;
	rtn.append((char*)&HEAD, sizeof(VIARCPHeadChunk));
	rtn.append((char*)&RETN, sizeof(VIARCPRetnChunk));
	for (auto i : DATA) {
		rtn.append((char*)&i, sizeof(VIARCPDataChunk) - sizeof(QByteArray));
		rtn.append(i.AllData);
	}
	return rtn;
}