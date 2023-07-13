#include "../VIPalette.h"

/*
VIPalette
*/
QStringList VIPalette::getColorNames()
{
	return ColorMap.keys();
}

QColor VIPalette::getColor(const QString &name)
{
	if (!ColorMap.contains(name)) {
		return QColor();
	}
	return ColorMap.value(name);
}

QColor VIPalette::getColor(DefaultColorName colorName)
{
	return getColor(getDefaultColorName(colorName));
}

void VIPalette::setColor(const QString &name, const QColor &color)
{
	if (ColorMap.contains(name)) {
		ColorMap.remove(name);
		ColorMap.insert(name, color);
		emit colorChanged(name, color);
		return;
	}
	ColorMap.insert(name, color);
}

void VIPalette::setColor(DefaultColorName colorName, const QColor &color)
{
	setColor(getDefaultColorName(colorName), color);
}

QString VIPalette::getDefaultColorName(DefaultColorName colorName)
{
	//We think that it is not necessary to give default color a explicit name.
	return QString("__DefaultColorName_" + QString::number((int)colorName))+"__";
}

/*
VIPaletteGroup
*/
def_init VIPaletteGroup::VIPaletteGroup():VIObject(){
	CurrentPalette = VI_NULLPTR;
}

void VIPaletteGroup::addPalette(const QString& name, VIColorMap cmap) {
	VIPalette* palette = new VIPalette(cmap);
	if (PaletteMap.contains(name)) {
		PaletteMap.remove(name);
	}
	if (PaletteMap.isEmpty()) {
		CurrentPalette = palette;
		CurrentPaletteName = name;
		ColorNames = palette->getColorNames();
	}
	PaletteMap.insert(name, palette);
	palette->setInPaletteGroup(true);
}

void VIPaletteGroup::addPalette(const QString&name, VIPalette* palette) {
	if (PaletteMap.contains(name)) {
		PaletteMap.remove(name);
	}
	if (PaletteMap.isEmpty()) {
		CurrentPalette = palette;
		CurrentPaletteName = name;
		ColorNames = palette->getColorNames();
	}
	PaletteMap.insert(name, palette);
	palette->setInPaletteGroup(true);
}

void VIPaletteGroup::removePalette(const QString& name) {
	if (PaletteMap.contains(name)) {
		VIPalette* palette = PaletteMap.value(name);
		PaletteMap.remove(name);
		if (palette == CurrentPalette) {
			if (PaletteMap.isEmpty()) {
				CurrentPalette = VI_NULLPTR;
				CurrentPaletteName = "";
			}
			else {
				CurrentPaletteName = PaletteMap.keys().first();
				CurrentPalette = PaletteMap[CurrentPaletteName];
			}
		}	
		delete palette;
		emit paletteChanged(name);
	}
}

QStringList VIPaletteGroup::getPaletteNames() {
	return PaletteMap.keys();
}

void VIPaletteGroup::changeCurrentPalette(const QString& name) {
	if (PaletteMap.contains(name)) {
		CurrentPalette = PaletteMap.value(name);
		CurrentPaletteName = name;
		ColorNames = CurrentPalette->getColorNames();
		emit paletteChanged(name);
	}
}

QColor VIPaletteGroup::getColor(const QString& colorName) {
	if (CurrentPalette == VI_NULLPTR) {
		return QColor();
	}
	return CurrentPalette->getColor(colorName);
}

QColor VIPaletteGroup::getColor(VIPalette::DefaultColorName colorName) {
	if (CurrentPalette == VI_NULLPTR) {
		return QColor();
	}
	return CurrentPalette->getColor(colorName);
}

QColor VIPaletteGroup::getColorFromPalette(const QString& paletteName, const QString& colorName) {
	if (PaletteMap.contains(paletteName)) {
		return PaletteMap.value(paletteName)->getColor(colorName);
	}
	return QColor();
}

void VIPaletteGroup::setColor(const QString& colorName, const QColor& color) {
	if (CurrentPalette == VI_NULLPTR) {
		return;
	}
	CurrentPalette->setColor(colorName, color);
}

void VIPaletteGroup::setColor(VIPalette::DefaultColorName colorName, const QColor& color) {
	if (CurrentPalette == VI_NULLPTR) {
		return;
	}
	CurrentPalette->setColor(colorName, color);
}

void VIPaletteGroup::setColorToPalette(const QString& paletteName, const QString& colorName, const QColor& color) {
	if (PaletteMap.contains(paletteName)) {
		PaletteMap.value(paletteName)->setColor(colorName, color);
	}
}
