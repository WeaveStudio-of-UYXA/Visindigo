#include "../VIARCPRemoteObject.h"
#include "../VIARCPPeerPort.h"

void VIARCPRemoteCallRouter::preOnRemoteCall(VIARCPCallDataObject& obj, VIARCPSocket* who) {

	Who = who;
	if (obj.getDataChunkLength() != TypeNames.length()) {
		RET.setStatusCode(VIARCPEnum::Status::ParmeterCountMismatch);
		Who->sendData(RET);
		return;
	}
	for (auto i = 0; i < obj.getDataChunkLength(); i++) {
		auto s = VIARCPTypeManager::checkData(obj.getDataChunk(i), TypeNames[i]);
		switch (s) {
		case VIARCPEnum::Status::Success:
			break;
		default:
			VIARCPReturnDataObject ret;
			ret.setStatusCode(s);
			Who->sendData(ret);
			return;
		}
	}
	onRemoteCall(obj.getDataChunks(), who);
	Who->sendData(RET);
	RET.clearChunks();
}
void VIARCPRemoteCallRouter::setStatusCode(VIARCPEnum::Status code) {
	RET.setStatusCode(code);
}
void VIARCPRemoteCallRouter::addReturnData(VIARCPDataChunk& data) {
	RET.addDataChunk(data);
}



void VIARCPRemoteCaller::setFunctionName(QString name) {
	Call.setFunctionName(name);
}
void VIARCPRemoteCaller::addDataChunk(VIARCPDataChunk& data) {
	Call.addDataChunk(data);
}
void VIARCPRemoteCaller::setWho(VIARCPSocket* who) {
	Who = who;
}
void VIARCPRemoteCaller::setPort(VIARCPPeerPort* port) {
	Port = port;
}
void VIARCPRemoteCaller::doRemoteCall() {
	if (Port == VI_NULL || Who == VI_NULL) {
		return;
	}
	Port->doRemoterCall(this);
	Call.clearChunks();
}
void VIARCPRemoteCaller::preOnReturn(VIARCPReturnDataObject& obj) {
	onReturn(obj.getDataChunks());
}



