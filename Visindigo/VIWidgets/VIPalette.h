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
	_Public static QString getDefaultColorName(DefaultColorName colorName);
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
	_Public void setColorToPalette(const QString& paletteName, VIPalette::DefaultColorName colorName, const QColor& color);
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
	_Public def_init private_VIPaletteChangeAnimationBehavior(VIPaletteGroup* parent);
	_Public void setColorMap(const VIColorMap& raw, const VIColorMap& target);
	_Public virtual void onStart() override;
	_Public virtual void onTick() override;
	_Public virtual void onStop()override;
};
