#include "../VIGridTexture.h"

def_init VIGridTexture::VIGridTexture(VISuper* parent) :VIObject(parent) {
	json.setDefaultFromStr("{\"Row\": 1,\"Column\":1,\"Effective\":1,\"Loop\":0, \"Fps\":32}");
};
bool VIGridTexture::load(const QString& configPath) {
	if (Playing) {
		return false;
	}
	if (configPath.isEmpty()) {
		return false;
	}
	if (!QFile::exists(configPath + ".json")) {
		return false;
	}
	ConfigPath = configPath;
	if (!QFile::exists(configPath + ".png")) {
		return false;
	}
	json.loadSettings(configPath + ".json");
	int Row = json.getValueOf("Row").toInt();
	int Column = json.getValueOf("Column").toInt();
	int Effective = json.getValueOf("Effective").toInt();
	Loop = json.getValueOf("Loop").toInt();
	Fps = json.getValueOf("Fps").toInt();
	Row = Row > 0 ? Row : 1;
	Column = Column > 0 ? Column : 1;
	Effective = Effective > 0 ? Effective : Row * Column;
	Loop = Loop > 0 ? Loop : 0;
	Loop = Loop > Effective ? 0 : Loop;
	Fps = Fps > 0 ? Fps : 32;
	QImage image(configPath + ".png");
	int width = image.width() / Column;
	int height = image.height() / Row;
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Column; j++) {
			if (Textures.size() >= Effective) {
				break;
			}
			QImage img = image.copy(j * width, i * height, width, height);
			Textures.append(img);
		}
	}
	consoleLog("Load GridTexture: " + configPath + ", frame: " + QString::number(Textures.size()));
	return true;
}
bool VIGridTexture::isPlaying() {
	return Playing;
}
const QImage& VIGridTexture::operator[](int index) {
	return Textures[index];
}
const QImage VIGridTexture::getImage(int index) {
	return Textures[index];
}
void VIGridTexture::appendImage(QImage image) {
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
QSize VIGridTexture::getImageSize() {
	if (Textures.isEmpty()) {
		return QSize(0, 0);
	}
	return Textures[0].size();
}
int VIGridTexture::getSize() {
	return Textures.size();
}
int VIGridTexture::getFps() {
	return Fps;
}
int VIGridTexture::getLoop() {
	return Loop;
}
void VIGridTexture::setFps(int fps) {
	if (Playing) {
		return;
	}
	Fps = fps;
	json.setValueOf("Fps", Fps);
}
void VIGridTexture::setLoop(int loop) {
	if (Playing) {
		return;
	}
	Loop = loop;
	json.setValueOf("Loop", Loop);
}
void VIGridTexture::save() {
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
	QImage image(width * Column, height * Row, QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QPainter painter(&image);
	for (int i = 0; i < Textures.size(); i++) {
		int row = i / Column;
		int column = i % Column;
		painter.drawImage(column * width, row * height, Textures[i]);
	}
	painter.end();
	image.save(ConfigPath + ".png");
	json.setValueOf("Row", Row);
	json.setValueOf("Column", Column);
	json.saveSettings(ConfigPath + ".json");
}


def_init VIGridTextureAbstractDriver::VIGridTextureAbstractDriver(QObject* parent) :VIAnimationBehavior(parent) {
	this->setForeverDuration();
};
void VIGridTextureAbstractDriver::setGridTexture(VIGridTexture* gridTexture) {
	if (this->BehaviorState == Visindigo::Idle) {
		GridTexture = gridTexture;
	}
}
void VIGridTextureAbstractDriver::start(Visindigo::QuantifyTickType){
	if (GridTexture == VI_NULL) {
		return;
	}
	if (GridTexture->getImageSize().isEmpty()) {
		return;
	}
	GridTexture->Playing = true;
	switch (GridTexture->getFps()) {
	case 32:
		VIAnimationBehavior::start(Visindigo::T32);
		return;
	case 64:
		VIAnimationBehavior::start(Visindigo::T64);
		return;
	case 128:
		VIAnimationBehavior::start(Visindigo::T128);
		return;
	default:
		VIAnimationBehavior::start(Visindigo::T32);
		return;
	}
}
void VIGridTextureAbstractDriver::onStart() HalfVirtual;
void VIGridTextureAbstractDriver::onTick(){
	if (Index < GridTexture->getSize()) {
		onImage(GridTexture->getImage(Index));
		Index++;
	}
	else {
		if (GridTexture->getLoop() < 0) {
			stop();
		}
		else {
			Index = GridTexture->getLoop();
		}
	}
}
void VIGridTextureAbstractDriver::onStop() {
	GridTexture->Playing = false;
	Index = 0;
}
