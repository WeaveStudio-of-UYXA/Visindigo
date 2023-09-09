#include "../VIARCPSocket.h"


def_init VIARCPSocket::VIARCPSocket(QTcpSocket* s) {
	setTcpSocket(s);
}
QString VIARCPSocket::getRandomString(int length) {
	QString str;
	for (int i = 0; i < length; i++) {
		str.append(QChar('A' + qrand() % 26));
	}
	return str;
}
void VIARCPSocket::reConnect() {
	if (reconnectCount >= maxReconnect) {
		consoleLog(VIConsole::inErrorStyle("Max auto reconnect count reached, aborting."));
		return;
	}
	else {
		reconnectCount++;
		consoleLog(VIConsole::inWarningStyle(QString("Auto reconnecting, count: %1, max: %2").arg(reconnectCount).arg(maxReconnect)));
	}
	Socket->connectToHost(Socket->peerAddress(), Socket->peerPort());
}
void VIARCPSocket::setMaxReconnectCount(quint8 count) {
	maxReconnect = count;
}
void VIARCPSocket::setTcpSocket(QTcpSocket* s) {
	Socket = s;
	QString ConnectionInfo = QString("%1:%2").arg(Socket->peerAddress().toString()).arg(Socket->peerPort());
	setObjectName(ConnectionInfo);
	connect(Socket, &QTcpSocket::readyRead, this, &VIARCPSocket::handleData);
	connect(Socket, &QTcpSocket::connected, this, &VIARCPSocket::onConnected);
	connect(Socket, &QTcpSocket::disconnected, this, &VIARCPSocket::onDisconnected);
	connect(Socket, &QTcpSocket::errorOccurred, this, &VIARCPSocket::onErrorOccurred);
}
void VIARCPSocket::onConnected() {
	emit connected(this);
	reconnectCount = 0;
	VIARCPCallDataObject obj("terminal");
	obj.addDataChunk(VIARCPTypeManager::fromString("Visindigo ARCP Client"));
	RandomString = getRandomString();
	obj.addDataChunk(VIARCPTypeManager::fromString(RandomString));
	sendData(obj);
	
}
void VIARCPSocket::onDisconnected() {
	consoleLog("Connection lost");
	Cache.clear();
	emit disconnected(this);
}
void VIARCPSocket::onErrorOccurred(QAbstractSocket::SocketError error) {
	consoleLog(VIConsole::inErrorStyle(QString("Socket error occurred: %1").arg(error)));
	if (!AsServer) {
		reConnect();
	}
}
void VIARCPSocket::sendData(VIARCPCallDataObject& obj) {
	Socket->write(obj.toByte());
	debugOutput(obj, false);
}
void VIARCPSocket::sendData(VIARCPReturnDataObject& obj) {
	Socket->write(obj.toByte());
	debugOutput(obj, false);
}
void VIARCPSocket::handleData() {
	Cache.append(Socket->readAll());
	if (Cache.size() == 0xFFFFFFFF) {
		consoleLog("===Cache is too large===");
		Socket->disconnectFromHost();
		onDisconnected();
		return;
	}
	VIConsole::printBinary(Cache);
	handleCache();
}
void VIARCPSocket::handleCache() {
	while (true) {
		if (Cache.size() < sizeof(quint32) + sizeof(quint16)) {
			break;
		}
		quint32 L1;
		memcpy(&L1, Cache.data(), sizeof(quint32));
		quint16 L2;
		memcpy(&L2, Cache.data() + sizeof(quint32), sizeof(quint16));
		if (Cache.size() < sizeof(quint32) + sizeof(quint16) + L1 + L2) {
			break;
		}
		else {
			VIARCPDataChunk chunk;
			chunk.DataLength = L1;
			chunk.TypeNameLength = L2;
			if (L1 + L2 != 0) {
				chunk.AllData = QByteArray(Cache.data() + sizeof(quint32) + sizeof(quint16), L1 + L2);
			}
			Cache.remove(0, sizeof(quint32) + sizeof(quint16) + L1 + L2);
			VIARCPEnum::Status code = onChunkData(chunk);
			switch (code) {
			case VIARCPEnum::Status::Success:
				break;
			case VIARCPEnum::Status::HeadChunkLengthIsNotARCP:
			case VIARCPEnum::Status::HeadChunkIsNotARCP:
			case VIARCPEnum::Status::UnknownProtocalVersion:
			case VIARCPEnum::Status::IncorrectCALLorRETNChunk:
			case VIARCPEnum::Status::MissingCALLChunk:
			case VIARCPEnum::Status::MissingRETNChunk:
				Socket->disconnectFromHost();
				onDisconnected();
				break;
			}
		}
	}
}
VIARCPEnum::Status VIARCPSocket::onChunkData(const VIARCPDataChunk& chunk) {
	if (DataChunkList.size() == 0) {
		VIARCPHeadChunk head;
		if (chunk.DataLength + chunk.TypeNameLength != sizeof(VIARCPHeadChunk)-sizeof(quint32)-sizeof(quint16)) {
			consoleLog(VIConsole::inWarningStyle("Head length error"));
			return VIARCPEnum::Status::HeadChunkLengthIsNotARCP;
		}
		head.DataLength = chunk.DataLength;
		head.VersionNameLength = chunk.TypeNameLength;
		memcpy(&head.TagData, chunk.AllData, sizeof(quint32));
		memcpy(&head.Version, chunk.AllData.data() + sizeof(quint64), sizeof(quint16));
		if (head.TagData != ARCP_CONST_ARCPRNRN) {
			consoleLog(VIConsole::inWarningStyle("Head is not ARCP"));
			disconnect();
			return VIARCPEnum::Status::HeadChunkIsNotARCP;
		}
		switch ((VIARCPEnum::Version)head.Version) {
		case VIARCPEnum::Version::Latest:
			break;
		default:
			consoleLog(VIConsole::inWarningStyle("Unknown protocal version"));
			return VIARCPEnum::Status::UnknownProtocalVersion;
		}
		Head = head;
	}
	else if (DataChunkList.size() == 1) {
		if (chunk.DataLength != ARCP_UINT32_8) {
			consoleLog(VIConsole::inWarningStyle("CALL or RETN length error"));
			return VIARCPEnum::Status::IncorrectCALLorRETNChunk;
		}
		if (chunk.DataLength + chunk.TypeNameLength != chunk.AllData.size()) {
			consoleLog(VIConsole::inWarningStyle("CALL or RETN length error"));
			return VIARCPEnum::Status::IncorrectCALLorRETNChunk;
		}
		quint32 tag;
		memcpy(&tag, chunk.AllData.data(), sizeof(quint32));
		if (tag == ARCP_CONST_RETN) {
			VIARCPRetnChunk retn;
			retn.DataLength = chunk.DataLength;
			retn.StatusCodeLength = chunk.TypeNameLength;
			memcpy(&retn.TagData, chunk.AllData, sizeof(quint32));
			memcpy(&retn.ParaCount, chunk.AllData.data() + sizeof(quint32), sizeof(quint32));
			memcpy(&retn.StatusCode, chunk.AllData.data() + sizeof(quint32) + sizeof(quint32), sizeof(quint16));
			Retn = retn;
			GetCallOrRetn = false;
			ParaCount = retn.ParaCount;
		}
		else if (tag == ARCP_CONST_CALL) {
			VIARCPCallChunk call;
			call.DataLength = chunk.DataLength;
			call.FunctionNameLength = chunk.TypeNameLength;
			memcpy(&call.TagData, chunk.AllData, sizeof(quint32));
			memcpy(&call.ParaCount, chunk.AllData.data() + sizeof(quint32), sizeof(quint32));
			call.FunctionName = chunk.AllData.right(chunk.TypeNameLength);
			Call = call;
			GetCallOrRetn = true;
			ParaCount = call.ParaCount;
		}
		else {
			return VIARCPEnum::Status::IncorrectCALLorRETNChunk;
		}
	}
	DataChunkList.append(chunk);
	if (DataChunkList.size() - 2 == ParaCount) {
		DataChunkList.removeFirst();
		DataChunkList.removeFirst();
		if (!GetCallOrRetn) {
			VIARCPReturnDataObject obj = VIARCPReturnDataObject(Head, Retn, DataChunkList);
			debugOutput(obj, true);
			emit remoteReturnDataPrepared(this, obj);
		}
		else {
			VIARCPCallDataObject obj = VIARCPCallDataObject(Head, Call, DataChunkList);
			debugOutput(obj, true);
			emit remoteCallDataPrepared(this, obj);
		}
		DataChunkList.clear();
	}
	return VIARCPEnum::Status::Success;
}
void VIARCPSocket::debugOutput(VIARCPCallDataObject& obj, bool get) {
	if (get) {
		consoleLog("Get Remote Call: " + obj.getFunctionName());
	}
	else {
		consoleLog("Send Remote Call: " + obj.getFunctionName());
	}
	int j = 0;
	for (auto i : obj.getDataChunks()) {
		if (VIARCPTypeManager::checkData(i, VIARCPTypeManager::TypeName::String) == VIARCPEnum::Success) {
			consoleLog("\t para " + QString::number(j) + " (type: " + QString::fromUtf8(i.AllData.right(i.TypeNameLength)) + "): "
				+ QString::fromUtf8(i.AllData.left(i.DataLength)));
		}
		else {
			consoleLog("\t para " + QString::number(j) + " (type: " + QString::fromUtf8(i.AllData.right(i.TypeNameLength)) + "): "
				+ i.AllData.left(i.DataLength));
		}
		j++;
	}
}
void VIARCPSocket::debugOutput(VIARCPReturnDataObject& obj, bool get) {
	if (get) {
		consoleLog("Get Remote Return: " + QString::number(obj.getStatusCode(), 16) + " (" +
			VIARCPEnum::getStatusStr(obj.getStatusCode()) + ")");
	}
	else {
		consoleLog("Send Remote Return: " + QString::number(obj.getStatusCode(), 16) + " (" +
			VIARCPEnum::getStatusStr(obj.getStatusCode()) + ")");
	}
	int j = 0;
	for (auto i : obj.getDataChunks()) {
		if (VIARCPTypeManager::checkData(i, VIARCPTypeManager::TypeName::String) == VIARCPEnum::Success) {
			consoleLog("\t para " + QString::number(j) + " (type: " + QString::fromUtf8(i.AllData.right(i.TypeNameLength)) + "): "
				+ QString::fromUtf8(i.AllData.left(i.DataLength)));
		}
		else {
			consoleLog("\t para " + QString::number(j) + " (type: " + QString::fromUtf8(i.AllData.right(i.TypeNameLength)) + "): "
				+ i.AllData.left(i.DataLength));
		}
		j++;
	}
}
