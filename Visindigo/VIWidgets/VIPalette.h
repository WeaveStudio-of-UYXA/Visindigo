#pragma once
#include "../VICore/VICore.h"

typedef QHash<QString, QColor> VIColorMap;
class VIPublicAPI VIPaletteGroup;
class VIPublicAPI private_VIPaletteChangeAnimationBehavior;

class VIPublicAPI VIPalette :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIPaletteGroup;
	friend class private_VIPaletteChangeAnimationBehavior;
	_Public enum class DefaultColorName {
		Background, Foreground,
		Hover, Selected, Active, Disabled,
		Border, BorderHover, BorderSelected, BorderActive, BorderDisabled,
		Text, TextHover, TextSelected, TextActive, TextDisabled,
	};
	_Signal void colorChanged(QString colorName, QColor color);
	VI_ProtectedProperty(VIColorMap, ColorMap);
	VI_ProtectedFlag(InPaletteGroup);
	_Public def_init VIPalette(VIColorMap cmap = {}) :VIObject() { 
		InPaletteGroup = false;
		ColorMap = cmap; 
	}
	_Public QStringList getColorNames();
	_Public QColor getColor(const QString& colorName);
	_Public QColor getColor(DefaultColorName colorName);
	_Public void setColor(const QString& colorName, const QColor& color);
	_Public void setColor(DefaultColorName colorName, const QColor& color);
	_Private static QString getDefaultColorName(DefaultColorName colorName);
};


class VIPublicAPI VIPaletteGroup :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Singleton(VIPaletteGroup);
	friend class private_VIPaletteChangeAnimationBehavior;
	_Signal void paletteChanged(QString paletteName);
	_Signal void colorChanged(QString paletteName, QString colorName, QColor color);
	_Protected QMap<QString, VIPalette*> PaletteMap;
	_Private VIPalette* CurrentPalette;
	_Private private_VIPaletteChangeAnimationBehavior* ChangeAnimationBehavior;
	VI_PrivateProperty(QStringList, ColorNames);
	VI_PrivateProperty(QString, CurrentPaletteName);
	VI_Flag(ChangePaletteUseAnimation);
	_Public def_init VIPaletteGroup();
	_Public void addPalette(const QString& paletteName, VIColorMap cmap = {});
	_Public void addPalette(const QString& paletteName, VIPalette* palette);
	_Public void removePalette(const QString& paletteName);
	_Public QStringList getPaletteNames();
	_Public void changeCurrentPalette(const QString& paletteName);
	_Public QColor getColor(const QString& colorName);
	_Public QColor getColor(VIPalette::DefaultColorName colorName);
	_Public QColor getColorFromPalette(const QString& paletteName, const QString& colorName);
	_Public void setColor(const QString& colorName, const QColor& color);
	_Public void setColor(VIPalette::DefaultColorName colorName, const QColor& color);
	_Public void setColorToPalette(const QString& paletteName, const QString& colorName, const QColor& color);
	_Public void onPaletteChanged(const QString& raw, const QString& cur);
};

class VIPublicAPI private_VIPaletteChangeAnimationBehavior :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIPaletteGroup;
	_Private struct VectorColor {
		int r, g, b, a;
	};
	VI_ProtectedProperty(VIPaletteGroup*, Group);
	VI_ProtectedProperty(QString, TargetPaletteName);
	_Private VIColorMap RawColorMap;
	_Private VIColorMap CachedColorMap;
	_Private VIColorMap CurrentColorMap;
	_Private QMap<QString, VectorColor> DeltaColorMap;
	_Public def_init private_VIPaletteChangeAnimationBehavior(VISuper* parent) :VIAnimationBehavior(parent) {
	}
	_Public void setColorMap(const VIColorMap& raw, const VIColorMap& target) {
		RawColorMap = raw;
		CachedColorMap = target;
		DeltaColorMap.clear();
		CurrentColorMap.clear();
		for (auto colorName : CachedColorMap.keys()) {
			auto color = CachedColorMap[colorName];
			auto rawColor = RawColorMap[colorName];
			DeltaColorMap[colorName] = {
				color.red() - rawColor.red(),
				color.green() - rawColor.green(),
				color.blue() - rawColor.blue(),
				color.alpha() - rawColor.alpha()
			};
		}
	}
	_Public virtual void onActive() override {
	}
	_Public virtual void onTick() override {
		float p = VICommonMapping::sin_0_1(Duration->getPercent());
		for (auto colorName : CachedColorMap.keys()) {
			CurrentColorMap[colorName] = QColor(
				RawColorMap[colorName].red() + DeltaColorMap[colorName].r * p,
				RawColorMap[colorName].green() + DeltaColorMap[colorName].g * p,
				RawColorMap[colorName].blue() + DeltaColorMap[colorName].b * p,
				RawColorMap[colorName].alpha() + DeltaColorMap[colorName].a * p
			);
		}
		Group->PaletteMap[TargetPaletteName]->setColorMap(CurrentColorMap);
		emit Group->paletteChanged(TargetPaletteName);
	}
	_Public virtual void onSubside()override {
		Group->PaletteMap[TargetPaletteName]->setColorMap(CurrentColorMap);
	}
};

