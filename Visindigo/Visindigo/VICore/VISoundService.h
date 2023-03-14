#pragma once
#include <QtCore>
#include <QTest>
#include <QtMultiMedia>
#include "macro/VIMarco.h"
#include "VIGeneralBehavior.h"
#include "macro/VISoundService_m.h"
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
	_Private VISoundServiceKey Key;
	_Private bool IsDeleteWhenStop = false;
	_Private bool IsLoop = false;
	_Private bool PlayOnLoaded = false;
	_Private bool PrepareStop = true;
	_Private int maxVolume = 0;
	_Private def_init private_VIMediaPlayer(QObject* parent = Q_NULLPTR):QObject(this) {
		MediaPlayer = new QMediaPlayer(this);
		MediaPlayerList = new QMediaPlaylist(this);
		MediaPlayer->setPlaylist(MediaPlayerList);
		FadeBehavior = new private_VIMusicFadeBehavior(this);
		BIND(FadeBehavior, SIGNAL(getValue(int)), this->MediaPlayer, SLOT(controlVolume(int)));
		connect(MediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onPlayerStateChanged(QMediaPlayer::State)));
	}
	_Private void setVolume(int volume) {
		MediaPlayer->setVolume(volume);
		maxVolume = volume;
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
	_Public void playOnLoaded(bool set) {
		PlayOnLoaded = set;
	}
	_Private void play() {
		MediaPlayerList->setPlaybackMode(IsLoop ? QMediaPlaylist::PlaybackMode::Loop : QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
		MediaPlayer->play();
		if (FadeInDuration != 0) {
			FadeBehavior->setMaxVolume(maxVolume);
			FadeBehavior->setFadeDuration(FadeInDuration, true);
			FadeBehavior->active();
		}
	}
	_Private void stop() {
		if (FadeOutDuration != 0) {
			PrepareStop = true;
			FadeBehavior->setMaxVolume(maxVolume);
			FadeBehavior->setFadeDuration(FadeOutDuration, false);
			FadeBehavior->active();
		}
		else {
			MediaPlayer->stop();
		}
	}
	_Slot void controlVolume(int volume) {
		MediaPlayer->setVolume(volume);
		if (PrepareStop&& volume == 0) {
			MediaPlayer->stop();
			PrepareStop = false;
		}
	}
	_Slot void onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
		if (status == QMediaPlayer::MediaStatus::LoadedMedia && PlayOnLoaded) {
			play();
		}
	}
	_Slot void onPlayerStateChanged(QMediaPlayer::State state) {
		MediaPlayerList->clear();
		emit playerIsIdle();
		if (state == QMediaPlayer::State::StoppedState && IsDeleteWhenStop) {
			this->disconnect();
			this->deleteLater();
		}
	}
	_Private bool isIdle() {
		return MediaPlayer->state() == QMediaPlayer::State::StoppedState;
	}
};
class VISoundService :public QObject
{
	Q_OBJECT;
	_Public QMap<VISoundServiceKey, private_VIMediaPlayer*> PlayerPool;
	_Public QQueue<private_VIMediaPlayer*> IdlePool;
	_Public VISoundServiceKey KeyCounter = 0;
	_Private bool doNotGC = false;
	_Public def_init VISoundService(QObject* parent = Q_NULLPTR) :QObject(parent) { 
		private_VIMediaPlayer* Player = new private_VIMediaPlayer(this);
		IdlePool.append(Player);
		connect(Player, SIGNAL(playerIsIdle()), this, SLOT(onSomeoneIdle()));
	}
	_Public VISoundServiceKey addSound(QString PathName, int volume, 
		bool isLoop = false, VIMilliSecond fadeIn = 0, 
		VIMilliSecond fadeOut = 0, bool playOnLoaded = true) {
		private_VIMediaPlayer* p;
		if (!IdlePool.isEmpty()) {
			p = IdlePool.dequeue();		
		}
		else {
			p = new private_VIMediaPlayer(this);
		}
		VISoundServiceKey key = this->setMediaPlayer(p, PathName, volume, isLoop, fadeIn, fadeOut, playOnLoaded);
		PlayerPool.insert(key, p);
		return key;
	}
	_Public VISoundServiceKey setSound(VISoundServiceKey key, QString PathName, int volume,
		bool isLoop = false, VIMilliSecond fadeIn = 0,
		VIMilliSecond fadeOut = 0, bool playOnLoaded = true) {
		doNotGC = true;
		private_VIMediaPlayer* p = PlayerPool.value(key);
		if (p != nullptr) {
			p->stop();
			PlayerPool.remove(key);
			VISoundServiceKey key = this->setMediaPlayer(p, PathName, volume, isLoop, fadeIn, fadeOut, playOnLoaded);
			PlayerPool.insert(key, p);
		}
		doNotGC = false;
		return key;
	}
	_Public void playSound(VISoundServiceKey key) {
		private_VIMediaPlayer* p = PlayerPool.value(key);
		if (p != nullptr) {
			p->play();
		}
	}
	_Public void stopSound(VISoundServiceKey key) {
		private_VIMediaPlayer* p = PlayerPool.value(key);
		if (p != nullptr) {
			p->stop();
		}
	}
	_Public void setVolume(VISoundServiceKey key, int volume) {
		private_VIMediaPlayer* p = PlayerPool.value(key);
		if (p != nullptr) {
			p->setVolume(volume);
		}
	}
	_Private VISoundServiceKey setMediaPlayer(private_VIMediaPlayer* p, QString PathName, int volume,
		bool isLoop = false, VIMilliSecond fadeIn = 0,
		VIMilliSecond fadeOut = 0, bool playOnLoaded = true) {
		p->setVolume(volume);
		p->setFadeInDuration(fadeIn);
		p->setFadeOutDuration(fadeOut);
		p->setLoop(isLoop);
		p->playOnLoaded(playOnLoaded);
		p->loadFrom(PathName);
		if (KeyCounter < 65535) { KeyCounter++; }
		else { KeyCounter = 0; }
		p->Key = KeyCounter;
		return KeyCounter;
	}
	private slots: void onSomeoneIdle() {
		private_VIMediaPlayer* player = static_cast<private_VIMediaPlayer*>(this->sender());
		VISoundServiceKey key = player->Key;
		PlayerPool.remove(key);
		IdlePool.enqueue(player);
		if (IdlePool.length() >= PlayerPool.keys().length() * 4) { garbageCollect(); }
	}
	_Slot void garbageCollect() {
		if (!doNotGC) {
			while (IdlePool.length() > 2) {
				private_VIMediaPlayer* p = IdlePool.dequeue();
				p->deleteLater();
			}
		}
	}
};