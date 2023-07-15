#include "../VIPalette.h"

VI_Singleton_Init(VIPaletteGroup);

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
	VI_CHECK_SingletonError(this);
	CurrentPalette = VI_NULLPTR;
	ChangePaletteUseAnimation = true;
	ChangeAnimationBehavior = new private_VIPaletteChangeAnimationBehavior(this);
	ChangeAnimationBehavior->setGroup(this);
	ChangeAnimationBehavior->setDuration(1000);
}

void VIPaletteGroup::addPalette(const QString& name, VIColorMap cmap) {
	if (name == CurrentPaletteName) {
		return;
	}
	VIPalette* palette = new VIPalette(cmap);
	if (PaletteMap.contains(name)) {
		removePalette(name);
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
	if (name == CurrentPaletteName) {
		return;
	}
	if (PaletteMap.contains(name)) {
		removePalette(name);
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
	if (name == CurrentPaletteName) {
		return;
	}
	if (PaletteMap.contains(name)) {
		VIPalette* palette = PaletteMap.value(name);
		PaletteMap.remove(name);
		delete palette;
	}
}

QStringList VIPaletteGroup::getPaletteNames() {
	return PaletteMap.keys();
}

void VIPaletteGroup::changeCurrentPalette(const QString& name) {
	if (PaletteMap.contains(name)) {
		QString oldName = CurrentPaletteName;
		CurrentPalette = PaletteMap.value(name);
		CurrentPaletteName = name;
		ColorNames = CurrentPalette->getColorNames();
		onPaletteChanged(oldName, CurrentPaletteName);
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

void VIPaletteGroup::onPaletteChanged(const QString& raw, const QString& cur) {
	if (ChangePaletteUseAnimation) {
		if (PaletteMap.contains(raw) && PaletteMap.contains(cur)) {
			ChangeAnimationBehavior->setColorMap(PaletteMap.value(raw)->getColorMap(), PaletteMap.value(cur)->getColorMap());
			ChangeAnimationBehavior->setTargetPaletteName(cur);
			ChangeAnimationBehavior->active();
		}
	}
	else {
		emit paletteChanged(cur);
	}
}