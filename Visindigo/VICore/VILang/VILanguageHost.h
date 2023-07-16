#pragma once
#include "../VIObject.h"

class VIPublicAPI VITranslationSubHost;

class VIPublicAPI VITranslatableObject
{
	VI_Property(VITranslationSubHost*, TRHost);
	_Public virtual void onTranslating() PureVirtual;
};

class VIPublicAPI VITranslationSubHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QVector<VITranslatableObject*> TargetList;
	VI_Flag(UseGlobalSettings);
	_Public void addTranslatableObject(VITranslatableObject* target) {}
	_Public virtual void onGlobalLanguageChange() PureVirtual;
};