#pragma once
#include <QtCore>
#include <QTest>
#include <QtMultiMedia>
#include "../../../CommonEdit/CECore/CEMacro.h"
#include "VIGeneralBehavior.h"
class private_VIMusicFadeBehavior :public VIGeneralBehavior
{
	Q_OBJECT;
	_Signal void getValue(int);
	_Private int Volume = 0;
	_Private int CurrentVolume = 0;
	_Private bool IsFadeIn = false;
	_Public VIMilliSecond JUMPTIME;
	_Public def_init private_VIMusicFadeBehavior(QObject* parent = Q_NULLPTR) :VIGeneralBehavior(parent) {}
	_Public void setMaxVolume(int volume) {
		Volume = volume;
	}
	_Public void setFadeDuration(VIMilliSecond duration, bool isFadeIn = true) {
		this->setDuration(duration);
		IsFadeIn = isFadeIn;
	}
	_Protected void onActive() {
		CurrentVolume = 0;
		JUMPTIME = 0;
	}
	_Protected void onFrame() {
		JUMPTIME += getLastTime();
		if (JUMPTIME > 20) {
			if (IsFadeIn) {
				emit(getValue(this->getPercent(VIDuration::PercentType::Linear) * Volume));
			}
			else {
				emit(getValue(Volume - this->getPercent(VIDuration::PercentType::Linear) * Volume));
			}
		}
	}
	_Protected void onSkip() {
		this->setBehaviorState(VIGeneralBehavior::State::Done);
	}
	_Protected void onDone() {
		if (IsFadeIn) {
			emit(getValue(Volume));
		}
		else {
			emit(getValue(0));
		}
	}
};
class VISoundService; //QtCreator用于识别friend class
typedef int VISoundServiceKey;
class private_VIMediaPlayer :public QObject
{
	Q_OBJECT;
	friend class VISoundService;
	_Signal void playerIsIdle();
	_Public QMediaPlayer* MediaPlayer;
	_Public QMediaPlaylist* MediaPlayerList;
	_Private private_VIMusicFadeBehavior* FadeBehavior;
	_Private VIMilliSecond FadeInDuration = 0;
	_Private VIMilliSecond FadeOutDuration = 0;
	_Private bool IsDeleteWhenStop = false;
	_Private bool IsLoop = false;
	_Private VISoundServiceKey ServiceKey;
	_Private def_init private_VIMediaPlayer(QObject* parent = Q_NULLPTR) {
		MediaPlayer = new QMediaPlayer(parent);
		MediaPlayerList = new QMediaPlaylist(parent);
		MediaPlayer->setPlaylist(MediaPlayerList);
		FadeBehavior = new private_VIMusicFadeBehavior(parent);
		BIND(FadeBehavior, SIGNAL(getValue(int)), this->MediaPlayer, SLOT(controlVolume(int)));
		connect(MediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onPlayerStateChanged(QMediaPlayer::State)));
	}
	_Private void setVolume(int volume) {
		MediaPlayer->setVolume(volume);
		FadeBehavior->setMaxVolume(volume);
	}
	_Private void loadFrom(QString Path) {
		MediaPlayerList->clear();
		MediaPlayerList->addMedia(QUrl::fromLocalFile(Path));
	}
	_Private void setFadeInDuration(VIMilliSecond duration) {
		FadeInDuration = duration;
	}
	_Private void setFadeOutDuration(VIMilliSecond duration) {
		FadeOutDuration = duration;
	}
	_Private void setLoop(bool loop) {
		IsLoop = loop;
	}
	_Private void setAsDeleteWhenStop() {
		IsDeleteWhenStop = true;
	}
	_Private void play() {
		MediaPlayerList->setPlaybackMode(IsLoop ? QMediaPlaylist::PlaybackMode::Loop : QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
		MediaPlayer->play();
		FadeBehavior->setFadeDuration(FadeInDuration, true);
		FadeBehavior->active();
	}
	_Private void stop() {
		FadeBehavior->setFadeDuration(FadeOutDuration, false);
		FadeBehavior->active();
	}
	_Slot void controlVolume(int volume) {
		MediaPlayer->setVolume(volume);
		if (volume == 0) {
			MediaPlayer->stop();
		}
	}
	_Slot void onPlayerStateChanged(QMediaPlayer::State state) {
		emit playerIsIdle();
		if (state == QMediaPlayer::State::StoppedState && IsDeleteWhenStop) {
			this->disconnect();
			this->deleteLater();
		}
	}
	_Private bool isIdle() {
		return MediaPlayer->state() == QMediaPlayer::State::StoppedState;
	}
	_Private void setServiceKey(VISoundServiceKey key) {
		ServiceKey = key;
	}
	_Private VISoundServiceKey getServiceKey() {
		return ServiceKey;
	}
};
class VISoundService :public QObject
{
	Q_OBJECT;
	_Public QVector<private_VIMediaPlayer*> PlayerPool;
	_Public int IdlePlayer = 0;
	_Public def_init VISoundService(QObject* parent = Q_NULLPTR) :QObject(parent) { qsrand((unsigned)time(NULL)); }
	_Public VISoundServiceKey addSound(QString PathName, bool isLoop, VIMilliSecond fadeIn, VIMilliSecond fadeOut) {
		for (auto i = 0; i < PlayerPool.length(); i++) {
			if (PlayerPool[i]->isIdle()) {
				private_VIMediaPlayer* p = PlayerPool[i];
				p->loadFrom(PathName);
				p->setFadeInDuration(fadeIn);
				p->setFadeOutDuration(fadeOut);
				p->setLoop(isLoop);
				p->setServiceKey(qrand() % 65535);
				return p->getServiceKey() * (i);
			}
		}
		private_VIMediaPlayer* newPlayer = new private_VIMediaPlayer(this);
		PlayerPool.append(newPlayer);
		newPlayer->loadFrom(PathName);
		newPlayer->setFadeInDuration(fadeIn);
		newPlayer->setFadeOutDuration(fadeOut);
		newPlayer->setLoop(isLoop);
		newPlayer->setServiceKey(qrand() % 65535);
		connect(newPlayer, SIGNAL(playerIsIdle()), this, SLOT(onSomeoneIdle()));
		return newPlayer->getServiceKey() * (PlayerPool.length() - 1);
	}
	_Public void playSound(VISoundServiceKey key) {
		for (int i = 0; i < PlayerPool.length(); i++) {
			if (PlayerPool.at(i)->getServiceKey() == key / (i)) {
				PlayerPool[i]->play();
			}
		}
	}
	_Public void stopSound(VISoundServiceKey key) {
		for (int i = 0; i < PlayerPool.length(); i++) {
			if (PlayerPool.at(i)->getServiceKey() == key / (i)) {
				PlayerPool[i]->stop();
			}
		}
	}
	_Slot void onSomeoneIdle() {
		IdlePlayer++;
		if (IdlePlayer * 2 > PlayerPool.length()) {
			for (auto i = PlayerPool.begin(); i != PlayerPool.end();) {
				if ((*i)->isIdle()) {
					delete (*i);
					i = PlayerPool.erase(i);
					continue;
				}
				else {
					i++;
				}
			}
		}
	}
};