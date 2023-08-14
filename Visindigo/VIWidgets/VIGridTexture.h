#pragma once
#include "../VICore/VICore.h"
#include "VIWidget.h"

class VIGridTextureLabelBehavior;
class VIGridTexture :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIGridTextureLabelBehavior;
	VI_Property(QString, ConfigPath);
	_Private QList<QImage> Textures;
	_Private VIDocument::VIJSON json;
	_Private int Loop = 0;
	_Private int Fps = 32;
	_Protected bool Playing = false;
	_Public def_init VIGridTexture(VISuper* parent = VI_NULL) :VIObject(parent) {
		json.setDefaultFromStr("{\"Row\": 1,\"Column\":1,\"Effective\":1,\"Loop\":0, \"Fps\":32}");
	};
	_Public bool load(const QString& configPath) {
		if (Playing) {
			return false;
		}
		if (configPath.isEmpty()) {
			return false;
		}
		if (!QFile::exists(configPath+".json")) {
			return false;
		}
		ConfigPath = configPath;
		if (!QFile::exists(configPath + ".png")) {
			return false;
		}
		json.loadSettings(configPath+".json");
		int Row = json.getValueOf("Row").toInt();
		int Column = json.getValueOf("Column").toInt();
		int Effective = json.getValueOf("Effective").toInt();
		Loop = json.getValueOf("Loop").toInt();
		Fps = json.getValueOf("Fps").toInt();
		Row = Row>0 ? Row : 1;
		Column = Column>0 ? Column : 1;
		Effective = Effective>0 ? Effective : 1;
		Loop = Loop>0 ? Loop : 0;
		Fps = Fps>0 ? Fps : 32;
		QImage image(configPath+ ".png");
		int width = image.width() / Column;
		int height = image.height() / Row;
		for (int i = 0; i < Row; i++) {
			for (int j = 0; j < Column; j++) {
				if (Textures.size() >= Effective) {
					break;
				}
				QImage img = image.copy(j*width, i*height, width, height);
				Textures.append(img);
			}
		}
		consoleLog("Load GridTexture: "+configPath+", frame: "+QString::number(Textures.size()));
		return true;
	}
	_Public bool isPlaying() {
		return Playing;
	}
	_Public const QImage& operator[](int index) {
		return Textures[index];
	}
	_Public const QImage getImage(int index) {
		return Textures[index];
	}
	_Public void appendImage(QImage image) {
		if (Playing) {
			return;
		}
		if (Textures.isEmpty()) {
			Textures.append(image);
			json.setValueOf("Effective", Textures.size());
			return;
		}
		if (image.size() != Textures[0].size()) {
			Textures.append(image.copy(0, 0, Textures[0].width(), Textures[0].height()));
			json.setValueOf("Effective", Textures.size());
			return;
		}
	}
	_Public QSize getImageSize() {
		if (Textures.isEmpty()) {
			return QSize(0, 0);
		}
		return Textures[0].size();
	}
	_Public int getSize() {
		return Textures.size();
	}
	_Public int getFps() {
		return Fps;
	}
	_Public int getLoop() {
		return Loop;
	}
	_Public void setFps(int fps) {
		if (Playing) {
			return;
		}
		Fps = fps;
		json.setValueOf("Fps", Fps);
	}
	_Public void setLoop(int loop) {
		if (Playing) {
			return;
		}
		Loop = loop;
		json.setValueOf("Loop", Loop);
	}
	_Public void save() {
		if (Playing) {
			return;
		}
		if (Textures.isEmpty()) {
			return;
		}
		if (ConfigPath.isEmpty()) {
			return;
		}
		int width = Textures[0].width();
		int height = Textures[0].height();
		int Row = qSqrt(Textures.size()) + 1;
		int Column = Row;
		QImage image(width*Column, height*Row, QImage::Format_ARGB32);
		image.fill(Qt::transparent);
		QPainter painter(&image);
		for (int i = 0; i < Textures.size(); i++) {
			int row = i / Column;
			int column = i % Column;
			painter.drawImage(column*width, row*height, Textures[i]);
		}
		painter.end();
		image.save(ConfigPath + ".png");
		json.setValueOf("Row", Row);
		json.setValueOf("Column", Column);
		json.saveSettings(ConfigPath + ".json");
	}
};

class VIGridTextureLabelBehavior :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QLabel* Master = VI_NULL;
	_Private VIGridTexture* GridTexture = VI_NULL;
	_Private int Index = 0;
	_Public def_init VIGridTextureLabelBehavior(QLabel* parent = VI_NULL) :VIAnimationBehavior(parent) {
		Master = parent;
		this->setForeverDuration();
	};
	_Public void setGridTexture(VIGridTexture* gridTexture) {
		if (this->BehaviorState == Visindigo::Idle) {
			GridTexture = gridTexture;
		}
	}
	_Public void active(Visindigo::QuantifyTickType = Visindigo::T64) override {
		if (GridTexture == VI_NULL) {
			return;
		}
		if (GridTexture->getImageSize().isEmpty()) {
			return;
		}
		GridTexture->Playing = true;
		switch (GridTexture->getFps()) {
		case 32:
			VIAnimationBehavior::active(Visindigo::T32);
			return;
		case 64:
			VIAnimationBehavior::active(Visindigo::T64);
			return;
		case 128:
			VIAnimationBehavior::active(Visindigo::T128);
			return;
		default:
			VIAnimationBehavior::active(Visindigo::T32);
			return;
		}
	}
	_Public void onActive()override {}
	_Public void onTick()override {
		if (Index < GridTexture->getSize()) {
			Master->setPixmap(QPixmap::fromImage(GridTexture->getImage(Index)));
			Index++;
		}
		else {
			if (GridTexture->getLoop() < 0) {
				subside();
			}
			else {
				Index = GridTexture->getLoop();
			}
		}
	}
	_Public void onSubside()override {
		GridTexture->Playing = false;
		Index = 0;
	}
};