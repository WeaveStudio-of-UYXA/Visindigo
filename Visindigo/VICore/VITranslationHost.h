#pragma once
#include "VIDocument/VITR.h"
#include "private/VisindigoNamespace.h"

class VIPublicAPI VITranslationSubHost;

class VIPublicAPI VITranslatableObject
{
	friend class VITranslationSubHost;
	_Private VITranslationSubHost* TRHost = VI_NULL;
	_Public VITranslationSubHost* getTRHost();
	_Public virtual void setTRHost(VITranslationSubHost* host);
	_Public virtual void onTranslating() HalfVirtual;
	_Public QString getTranslation(const QString& key);
	_Public def_del ~VITranslatableObject();
};

class VIPackageMeta;
class VITranslationHost;

class VIPublicAPI VITranslationSubHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VITranslationHost;
	friend class VIPackageMeta;
	_Public struct VITRFileInfo {
		QString FileName;
		bool inRC;
	};
	_Public QVector<VITranslatableObject*> TargetList;
	_Private QMap<Visindigo::Language, VITRFileInfo> LanguageFileNames;
	_Private VIDocument::VITR* CurrentDoc;
	_Private VIDocument::VITR* DefaultDoc;
	VI_PrivateProperty(Visindigo::Language, DefaultLanguage);
	_Private VIPackageMeta* ParentPackage;
	VI_Flag(UseGlobalSettings);
	_Public def_init VITranslationSubHost(VIPackageMeta* parent = VI_NULL);
	_Public void addTranslatableObject(VITranslatableObject* target);
	_Public void addTranslationFileName(Visindigo::Language langName, const QString& fileName, bool inRC = false);
	_Public void removeTranslatableObject(VITranslatableObject* target);
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