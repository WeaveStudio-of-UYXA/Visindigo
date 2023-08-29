#pragma once
#include "VIObject.h"
#include "VIConsole.h"
class VIPublicAPI VIRIFFObject : public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIRIFFObject;
	_Public enum class ChunkType{
		RIFF,
		LIST,
		Chunk,
		SubChunk = Chunk
	};
	_Protected qint32 ChunkID;
	_Protected QByteArray Data;
	_Protected QList<VIRIFFObject*> SubChunks;
	_Protected ChunkType Type;
	_Protected qint32 ChunkSize;
	_Protected qint32 FormType;
	_Public def_init VIRIFFObject(VISuper* parent = VI_NULL) :VIObject(parent) {
		
	}
	_Public void loadFrom(const QString& FileName) {
		QFile file(FileName);
		file.open(QIODevice::ReadOnly);
		QByteArray data = file.readAll();
		file.close();
		VIConsole::printLine(VIConsole::inNoticeStyle("Loading from file: " + FileName));
		loadFromByteArray(data);
	}
	_Public void loadFromByteArray(QByteArray data) {
		ChunkID = *(qint32*)data.mid(0, 4).data();
		ChunkSize = *(qint32*)data.mid(4, 4).data();
		if (ChunkID == 0x46464952) {
			Type = ChunkType::RIFF;
			FormType = *(qint32*)data.mid(8, 4).data();
			data = data.mid(12);
			while (data.size() > 0) {
				VIRIFFObject* obj = new VIRIFFObject(this);
				int size = obj->_loadFrom(data);
				SubChunks.append(obj);
				data = data.mid(size);
			}
		}
		else if (ChunkID == 0x5453494C) {
			Type = ChunkType::LIST;
			FormType = *(qint32*)data.mid(8, 4).data();
			data = data.mid(12);
			while (data.size() > 0) {
				VIRIFFObject* obj = new VIRIFFObject(this);
				int size = obj->_loadFrom(data);
				SubChunks.append(obj);
				data = data.mid(size);
			}
		}
		else {
			Type = ChunkType::Chunk;
			Data = data.mid(8, ChunkSize);
		}
	}
	_Private int _loadFrom(QByteArray data) {
		int size = 0;
		ChunkID = *(qint32*)data.mid(0, 4).data();
		ChunkSize = *(qint32*)data.mid(4, 4).data();
		data = data.mid(8, ChunkSize);
		size = 8 + ChunkSize;
		if (ChunkID == 0x46464952) {
			Type = ChunkType::RIFF;
			FormType = *(qint32*)data.mid(0, 4).data();
			data = data.mid(4);
			while (data.size() > 0) {
				VIRIFFObject* obj = new VIRIFFObject(this);
				int s = obj->_loadFrom(data);
				SubChunks.append(obj);
				data = data.mid(s);
			}
		}
		else if (ChunkID == 0x5453494C) {
			Type = ChunkType::LIST;
			FormType = *(qint32*)data.mid(0, 4).data();
			data = data.mid(4);
			while (data.size() > 0) {
				VIRIFFObject* obj = new VIRIFFObject(this);
				int s = obj->_loadFrom(data);
				SubChunks.append(obj);
				data = data.mid(s);
			}
		}
		else {
			Type = ChunkType::Chunk;
			Data = data;
		}
		return size;
	}
	_Public void printTree() {
		printTree(0);
	}
	_Private void printTree(int level) {
		QString str;
		for (int i = 0; i < 4; i++) {
			str += (char)(ChunkID >> (i * 8));
		}
		if (level == 0) {
			VIConsole::printLine(VIConsole::inNoticeStyle(QString("%1ChunkID: %2").arg(QString(level, '\t')).arg(str)));
			qDebug().noquote() << QString("%1ChunkSize: %2 Bytes").arg(QString(level, '\t')).arg(ChunkSize);
		}
		else {
			VIConsole::printLine(VIConsole::inNoticeStyle(QString("%1├ChunkID: %2").arg(QString(level, '\t')).arg(str)));
			qDebug().noquote() << QString("%1├ChunkSize: %2 Bytes").arg(QString(level, '\t')).arg(ChunkSize);
		}
		if (Type == ChunkType::RIFF) {
			QString str;
			for (int i = 0; i < 4; i++) {
				str += (char)(FormType >> (i * 8));
			}
			if (level == 0) {
				qDebug().noquote() << QString("%1FormType: %2").arg(QString(level, '\t')).arg(str);
				VIConsole::printLine(VIConsole::inSuccessStyle("%1SubChunks:").arg(QString(level, '\t')));
			}
			else {
				qDebug().noquote() << QString("%1├FormType: %2").arg(QString(level, '\t')).arg(str);
				VIConsole::printLine(VIConsole::inSuccessStyle("%1├SubChunks:").arg(QString(level, '\t')));
			}
			for (int i = 0; i < SubChunks.size(); i++) {
				SubChunks[i]->printTree(level + 1);
			}
		}
		else if (Type == ChunkType::LIST) {
			QString str;
			for (int i = 0; i < 4; i++) {
				str += (char)(FormType >> (i * 8));
			}
			if (level == 0) {
				qDebug().noquote() <<QString("%1ListType: %2").arg(QString(level, 'data')).arg(str);
				VIConsole::printLine(VIConsole::inSuccessStyle("%1SubChunks:").arg(QString(level, '\t')));
			}
			else {
				qDebug().noquote() <<QString("%1├ListType: %2").arg(QString(level, '\t')).arg(str);
				VIConsole::printLine(VIConsole::inSuccessStyle("%1├SubChunks:").arg(QString(level, '\t')));
			}
			for (int i = 0; i < SubChunks.size(); i++) {
				SubChunks[i]->printTree(level + 1);
			}
		}
		else {
			//将前32字节的数据转换为十六进制字符串
			QString dataAbstract;
			for (int i = 0; i < 32; i++) {
				if (i>=Data.size()) {
					break;
				}
				if (i % 2 == 0) {
					dataAbstract += " ";
				}
				dataAbstract += QString("%1").arg((quint8)Data.at(i), 2, 16, QChar('0')).toUpper();
			}
			if (level == 0) {
				qDebug().noquote() <<QString("%1Data: %2").arg(QString(level, '\t')).arg(dataAbstract+"...");
			}
			else {
				qDebug().noquote() <<QString("%1├Data: %2").arg(QString(level, '\t')).arg(dataAbstract+"...");
			}
		}
	}
	_Public QByteArray getDataOfChunk(qint32 chunkID) {
		for (int i = 0; i < SubChunks.size(); i++) {
			if (SubChunks[i]->ChunkID == chunkID) {
				return SubChunks[i]->Data;
			}
		}
		return QByteArray();
	}
	_Public QByteArray getDataOfChunk(QString chunkID) {
		return getDataOfChunk(*(qint32*)chunkID.toLocal8Bit().data());
	}
	_Public QByteArray getDataOfChunk(QList<qint32> chunkID) {
		if (chunkID.size() == 1) {
			return getDataOfChunk(chunkID[0]);
		}
		else {
			for(int i = 0; i < SubChunks.size(); i++) {
				if (SubChunks[i]->ChunkID == chunkID[0]) {
					return SubChunks[i]->getDataOfChunk(chunkID.mid(1));
				}
			}
		}
	}
	_Public QByteArray getDataOfChunk(QList<QString> chunkID) {
		QList<qint32> list;
		for (int i = 0; i < chunkID.size(); i++) {
			list.append(*(qint32*)chunkID[i].toLocal8Bit().data());
		}
		return getDataOfChunk(list);
	}
};