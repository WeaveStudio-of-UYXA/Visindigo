/*
Still under development
DO NOT USE IT IN PRODUCTION ENVIRONMENT
*/
#pragma once
#include "../VICore/VICore.h"
#include <QtMultimedia>

struct VIPublicAPI VIWaveHeadData {
	// This structure will be directly written to the file in binary format
	// So the order of the members is important
	// The size of this structure is 44 bytes
	// DO NOT CHANGE THE ORDER OF THE MEMBERS
	qint32 ChunkID;
	qint32 ChunkSize;
	qint32 Format;
	qint32 SubChunk1ID;
	qint32 SubChunk1Size;
	qint16 AudioFormat;
	qint16 NumChannels;
	qint32 SampleRate;
	qint32 ByteRate;
	qint16 BlockAlign;
	qint16 BitsPerSample;
	qint32 SubChunk2ID;
	qint32 SubChunk2Size;
};

class VIPublicAPI VIWaveData {
	_Private QVector<qint64> Data64;
	_Private QVector<qint32> Data32;
	_Private QVector<qint16> Data16;
	_Private QVector<qint8> Data8;
	_Private short sampleSize = 16;
	_Public void setSampleSize(short bit) {
		short i = bit % 8;
		sampleSize = (int)(bit / 8) * 8;
		if (i != 0) {
			sampleSize += 8;
		}
	}
	_Public void append(qint64 data) {
		switch (sampleSize) {
		case 8:
			Data8.push_back(data);
			break;
		case 16:
			Data16.push_back(data);
			break;
		case 32:
			Data32.push_back(data);
			break;
		case 64:
			Data64.push_back(data);
			break;
		}
	}
	_Public void prepend(qint64 data) {
		switch (sampleSize) {
		case 8:
			Data8.prepend(data);
			break;
		case 16:
			Data16.prepend(data);
			break;
		case 32:
			Data32.prepend(data);
			break;
		case 64:
			Data64.prepend(data);
			break;
		}
	}
	_Public qint64 operator[](int index) {
		switch (sampleSize) {
		case 8:
			return Data8[index];
		case 16:
			return Data16[index];
		case 32:
			return Data32[index];
		case 64:
			return Data64[index];
		}
	}
	_Public void set(int index, qint64 data) {
		switch (sampleSize) {
		case 8:
			Data8[index] = data;
			break;
		case 16:
			Data16[index] = data;
			break;
		case 32:
			Data32[index] = data;
			break;
		case 64:
			Data64[index] = data;
			break;
		}
	}
	_Public void insert(int index, qint64 data) {
		switch (sampleSize) {
		case 8:
			Data8.insert(index, data);
			break;
		case 16:
			Data16.insert(index, data);
			break;
		case 32:
			Data32.insert(index, data);
			break;
		case 64:
			Data64.insert(index, data);
			break;
		}
	}
	_Public void remove(int index) {
		switch (sampleSize) {
		case 8:
			Data8.remove(index);
			break;
		case 16:
			Data16.remove(index);
			break;
		case 32:
			Data32.remove(index);
			break;
		case 64:
			Data64.remove(index);
			break;
		}
	}
	_Public qint64 size() {
		switch (sampleSize) {
		case 8:
			return Data8.size();
		case 16:
			return Data16.size();
		case 32:
			return Data32.size();
		case 64:
			return Data64.size();
		}
	}
};
class VIPublicAPI VIOperationalWaveObject :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void finished();
	_Private QString FilePath;
	_Public VIWaveData RawData;
	_Public QAudioFormat AudioFormat;
	_Private QAudioDecoder decoder;
	_Public unsigned long long ReadIndex;
	VI_Property(float, Volume);
	_Public def_init VIOperationalWaveObject() {
		connect(&decoder, &QAudioDecoder::bufferReady, this, &VIOperationalWaveObject::_onBufferReady);
		connect(&decoder, &QAudioDecoder::finished, this, &VIOperationalWaveObject::onFinished);
		Volume = 1.0;
		FilePath = "";
	}
	_Public def_init VIOperationalWaveObject(QString filePath) {
		FilePath = filePath;
		decoder.setSourceFilename(filePath);
		connect(&decoder, &QAudioDecoder::bufferReady, this, &VIOperationalWaveObject::_onBufferReady);
		connect(&decoder, &QAudioDecoder::finished, this, &VIOperationalWaveObject::onFinished);
		Volume = 1.0;
	}
	_Public void load(QString filePath = "") {
		if (filePath != "") {
			FilePath = filePath;
			decoder.setSourceFilename(filePath);
		}
		decoder.start();
	}
	_Public void onFinished() {
		consoleLog("Finished");
		emit finished();
	}
	_Private void _onBufferReady() {
		AudioFormat = decoder.audioFormat();
		QAudioBuffer buffer = decoder.read();
		RawData.setSampleSize(AudioFormat.sampleSize());
		switch (AudioFormat.sampleSize()) {
		case 8:
			for (int i = 0; i < buffer.sampleCount(); i++) {
				RawData.append(((qint8*)buffer.constData())[i]);
			}
			break;
		case 16:
			for (int i = 0; i < buffer.sampleCount(); i++) {
				RawData.append(((qint16*)buffer.constData())[i]);
			}
			break;
		case 32:
			for (int i = 0; i < buffer.sampleCount(); i++) {
				RawData.append(((qint32*)buffer.constData())[i]);
			}
			break;
		}
	}
	_Public void append(VIMilliSecond ms) {
		for (int i = 0; i < ms * AudioFormat.sampleRate() * AudioFormat.channelCount() / 1000; i++) {
			RawData.append(0);
		}
	}
	_Public void prepend(VIMilliSecond ms) {
		for (int i = 0; i < get5MsCountForLength(ms) * get5MilliSecondSampleLength(); i++) {
			RawData.append(0);
		}
	}
	_Public void insert(VIMilliSecond ms, int index) {
		for (int i = 0; i < get5MsCountForLength(ms) * get5MilliSecondSampleLength(); i++) {
			RawData.insert(index, 0);
		}
	}
	_Public VIMilliSecond getSoundLength() {
		return ((long long)RawData.size() * 1000) / (AudioFormat.sampleRate() * AudioFormat.channelCount());
	}
	_Public quint64 getIndexOf(VIMilliSecond ms) {
		return get5MsCountForIndex(ms) * get5MilliSecondSampleLength();
	}
	_Public quint64 getSecondSampleLength() {
		return AudioFormat.sampleRate() * AudioFormat.channelCount();
	}
	_Public quint64 get5MilliSecondSampleLength() {
		// Visindigo uses 5ms as the shortest unit
		return getSecondSampleLength() / 200;
	}
	_Public	quint64 get5MsCountForLength(quint64 ms) {
		quint64 c = ms / 5;
		int r = ms % 5;
		if (r > 0) {
			c++;
		}
		return c;
	}
	_Public quint64 get5MsCountForIndex(quint64 ms) {
		return ms / 5;
	}
	_Public void mixSound(VIMilliSecond start, VIOperationalWaveObject& wave, VIMilliSecond tarStart = 0, VIMilliSecond tarEnd = -1) {
		if (tarEnd == -1) {
			tarEnd = wave.getSoundLength();
		}
		consoleLog("Current Wave Length: " + QString::number(getSoundLength()));
		if (start + tarEnd - tarStart > getSoundLength()) {
			append(start + tarEnd - tarStart - getSoundLength());
		}
		consoleLog("Current Wave Length: " + QString::number(getSoundLength()));
		int j = getIndexOf(start);

		for (int i = wave.getIndexOf(tarStart); i < wave.getIndexOf(tarEnd); i++) {
			// 由于序号以5ms为最小分度单位，因此末尾不足5ms的部分会被忽略
			if (j == RawData.size()) {
				break;
			}
			if (AudioFormat.channelCount() == wave.AudioFormat.channelCount()) {
				RawData.set(j, RawData[j] + wave.RawData[i] * wave.Volume);
			}
			else if (AudioFormat.channelCount() == 1 && wave.AudioFormat.channelCount() == 2) {
				RawData.set(j, RawData[j] + (wave.RawData[i] * 0.5 + wave.RawData[i + 1] * 0.5) * wave.Volume);
				i++;
			}
			else if (AudioFormat.channelCount() == 2 && wave.AudioFormat.channelCount() == 1) {
				RawData.set(j, RawData[j] + wave.RawData[i] * wave.Volume);
				RawData.set(j + 1, RawData[j + 1] + wave.RawData[i] * wave.Volume);
				j++;
			}
			j++;
		}
	}
	_Public void save(QString fileName) {
		QFile file(fileName);
		file.open(QIODevice::WriteOnly);
		VIWaveHeadData head;
		head.ChunkID = 0x46464952; // "RIFF"
		head.ChunkSize = 36 + RawData.size() * AudioFormat.sampleSize() / 8;
		head.Format = 0x45564157; // "WAVE"
		head.SubChunk1ID = 0x20746d66; // "fmt "
		head.SubChunk1Size = 16;
		head.AudioFormat = 1;
		head.NumChannels = AudioFormat.channelCount();
		head.SampleRate = AudioFormat.sampleRate();
		head.ByteRate = AudioFormat.sampleRate() * AudioFormat.channelCount() * AudioFormat.sampleSize() / 8;
		head.BlockAlign = AudioFormat.channelCount() * AudioFormat.sampleSize() / 8;
		head.BitsPerSample = AudioFormat.sampleSize();
		head.SubChunk2ID = 0x61746164; // "data"
		head.SubChunk2Size = RawData.size() * AudioFormat.sampleSize() / 8;
		file.write((char*)&head, sizeof(head));
		for (int i = 0; i < RawData.size(); i++) {
			qint64 data = RawData[i] * Volume;
			switch (AudioFormat.sampleSize()) {
			case 8:
				file.write((char*)&data, sizeof(qint8));
				break;
			case 16:
				file.write((char*)&data, sizeof(qint16));
				break;
			case 32:
				file.write((char*)&data, sizeof(qint32));
				break;
			}
		}
		file.close();
	}
};

class TestObject :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public VIOperationalWaveObject wave1;
	_Public VIOperationalWaveObject wave2;
	_Public int loadedCount = 0;
	_Public def_init TestObject() {
		wave1.load("E:/source/repos/VIWave/VIWave/t.wav");
		wave2.load("E:/source/repos/VIWave/VIWave/t2.wav");
		connect(&wave1, SIGNAL(finished()), this, SLOT(onLoaded()));
		connect(&wave2, SIGNAL(finished()), this, SLOT(onLoaded()));
	}
	_Slot void onLoaded() {
		loadedCount++;
		if (loadedCount == 2) {
			wave1.mixSound(5000, wave2);
			wave1.save("E:/source/repos/VIWave/VIWave/t3.wav");
		}
	}
};