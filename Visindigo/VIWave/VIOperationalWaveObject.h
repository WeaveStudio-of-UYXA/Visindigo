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

class VIPublicAPI VIOperationalWaveObject :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void finished();
	_Private QString FilePath;
	_Public QVector<qint32> RawData;
	_Public QAudioFormat AudioFormat;
	_Private QAudioDecoder decoder;
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
		emit finished();
	}
	_Private void _onBufferReady() {
		AudioFormat = decoder.audioFormat();
		QAudioBuffer buffer = decoder.read();
		switch (AudioFormat.sampleSize()) {
			case 8:
				for (int i = 0; i < buffer.sampleCount(); i++) {
					RawData.push_back(((qint8*)buffer.constData())[i]);
				}
				break;
			case 16:
				for (int i = 0; i < buffer.sampleCount(); i++) {
					RawData.push_back(((qint16*)buffer.constData())[i]);
				}
				break;
			case 32:
				for (int i = 0; i < buffer.sampleCount(); i++) {
					RawData.push_back(((qint32*)buffer.constData())[i]);
				}
				break;
		}
	}
	_Public void append(VIMilliSecond ms) {
		for (int i = 0; i < ms * AudioFormat.sampleRate() * AudioFormat.channelCount() / 1000; i++) {
			RawData.push_back(0);
		}
	}
	_Public void prepend(VIMilliSecond ms) {
		for (int i = 0; i < ms * AudioFormat.sampleRate() * AudioFormat.channelCount() / 1000; i++) {
			RawData.push_front(0);
		}
	}
	_Public void insert(VIMilliSecond ms, int index) {
		for (int i = 0; i < ms * AudioFormat.sampleRate() * AudioFormat.channelCount() / 1000; i++) {
			RawData.insert(index, 0);
		}
	}
	_Public VIMilliSecond getSoundLength() {
		return ((long long)RawData.size() * 1000) / (AudioFormat.sampleRate() * AudioFormat.channelCount());
	}
	_Public unsigned long long getIndexOf(VIMilliSecond ms) {
		return ms * AudioFormat.sampleRate() * AudioFormat.channelCount() / 1000;
	}
	_Public void mixSound(VIMilliSecond start, VIOperationalWaveObject& wave, VIMilliSecond tarStart = 0, VIMilliSecond tarEnd = -1) {
		if (tarEnd == -1) {
			tarEnd = wave.getSoundLength();
		}
		if (start + tarEnd - tarStart > getSoundLength()) {
			append(start + tarEnd - tarStart - getSoundLength());
		}
		int j = getIndexOf(start);
		for (int i = wave.getIndexOf(tarStart); i < wave.getIndexOf(tarEnd); i++) {
			if (j == RawData.size()) {
				break;
			}
			if (AudioFormat.channelCount() == wave.AudioFormat.channelCount()) {
				RawData[j] += wave.RawData[i] * wave.Volume;
			}
			else if (AudioFormat.channelCount() == 1 && wave.AudioFormat.channelCount() == 2) {
				RawData[j] += wave.RawData[i] * wave.Volume;
				i++;
			}
			else if (AudioFormat.channelCount() == 2 && wave.AudioFormat.channelCount() == 1) {
				RawData[j] += wave.RawData[i] * wave.Volume;
				RawData[j + 1] += wave.RawData[i] * wave.Volume;
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
			qint32 data = RawData[i] * Volume;
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