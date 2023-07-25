#pragma once
#include "VIDocument/VITR.h"
#include "private/VisindigoNamespace.h"

class VIPublicAPI VITranslationSubHost;

class VIPublicAPI VITranslatableObject
{
	VI_Property(VITranslationSubHost*, TRHost);
	_Public virtual void onTranslating() PureVirtual;
	_Public QString getTranslation(const QString& key);
};

class VIPackageInfo;
class VITranslationHost;

class VIPublicAPI VITranslationSubHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VITranslationHost;
	friend class VIPackageInfo;
	_Public struct VITRFileInfo{
		QString FileName;
		bool inRC;
	};
	_Public QVector<VITranslatableObject*> TargetList;
	_Private QMap<Visindigo::Language, VITRFileInfo> LanguageFileNames;
	_Private VIDocument::VITR* CurrentDoc;
	_Private VIDocument::VITR* DefaultDoc;
	VI_PrivateProperty(Visindigo::Language, DefaultLanguage);
	_Private VIPackageInfo* ParentPackage;
	VI_Flag(UseGlobalSettings);
	_Public def_init VITranslationSubHost(VIPackageInfo* parent = VI_NULL);
	_Public void addTranslatableObject(VITranslatableObject* target);
	_Public void addTranslationFileName(Visindigo::Language langName, const QString& fileName, bool inRC = false);
	_Public void onGlobalLanguageChange(Visindigo::Language langName);
	_Public void onInit();
	_Public QString getTranslation(const QString& key);
	_Private bool loadVITRDocument(VIDocument::VITR** docPtr, Visindigo::Language langName);
};

class VICoreFramework;

class VIPublicAPI VITopTranslationHandler :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public virtual QString onTopTranslation(const QString& key) PureVirtual;
};
class VIPublicAPI VITranslationHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VICoreFramework;
	_Private QVector<VITopTranslationHandler*> TopTranslationHandlers;
	_Protected def_init VITranslationHost(VISuper* parent = VI_NULL);
	_Protected void changeLanguage(Visindigo::Language langName);
	_Public QString topTranslation(const QString& key);
};