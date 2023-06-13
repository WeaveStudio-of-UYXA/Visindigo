#pragma once
#include "SPOLTerminal.h"
class SPOLWorkingEnv :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QString RootPath = "./UsersData/source";
	_Public QString BGIFolderPath = "BGI";
	_Public QString BGMFolderPath = "BGM";
	_Public QString NormalSoundFolderPath = "Sound";
	_Public QString CharacterSourceFolderPath = "Characte";
	_Public QString CacheRootPath = "./UsersData/cache";
	_Public SPOLAbstractTerminal* Terminal = VI_NULLPTR;
	_Public def_init SPOLWorkingEnv(VISuper* parent = VI_NULLPTR) :VIObject(parent) {}
	_Slot QString getPathOfBGI(const QString& name, bool cached) {
		if (cached) { return CacheRootPath + "/" + BGIFolderPath + "/" + name; }
		else { return BGIFolderPath + "/" + BGIFolderPath + "/" + name; }
	}
	_Slot QString getPathOfBGM(const QString& name, bool cached) {
		if (cached) { return CacheRootPath + "/" + BGMFolderPath + "/" + name; }
		else { return BGMFolderPath + "/" + BGMFolderPath + "/" + name; }
	}
	_Slot QString getPathOfNormalSound(const QString& name, bool cached) {
		if (cached) { return CacheRootPath + "/" + NormalSoundFolderPath + "/" + name; }
		else { return NormalSoundFolderPath + "/" + NormalSoundFolderPath + "/" + name; }
	}
	_Slot QString getPathOfCharacterSource(const QString& name, bool cached) {
		if (cached) { return CacheRootPath + "/" + CharacterSourceFolderPath + "/" + name; }
		else { return CharacterSourceFolderPath + "/" + CharacterSourceFolderPath + "/" + name; }
	}

};