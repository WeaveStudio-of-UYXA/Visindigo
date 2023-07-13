#pragma once
#include "../VICore/VICore.h"

typedef QHash<QString, QColor> VIColorMap;
class VIPaletteGroup;

class VIPalette :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIPaletteGroup;
	_Public enum class DefaultColorName {
		Background, Foreground,
		Hover, Selected, Active, Disabled,
		Border, BorderHover, BorderSelected, BorderActive, BorderDisabled,
		Text, TextHover, TextSelected, TextActive, TextDisabled,
	};
	_Signal void colorChanged(QString colorName, QColor color);
	_Private VIColorMap ColorMap;
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

class VIPaletteGroup :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void paletteChanged(QString paletteName);
	_Private QMap<QString, VIPalette*> PaletteMap;
	VI_PrivateProperty(QStringList, ColorNames);
	_Private VIPalette* CurrentPalette;
	VI_PrivateProperty(QString, CurrentPaletteName);
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
};