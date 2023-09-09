#include "../VIPalette.h"
#include "../VIWindowsTheme.h"
VI_Singleton_StaticInit(VIPaletteGroup);

/*
VIPalette
*/
QStringList VIPalette::getColorNames()
{
	return ColorMap.keys();
}

QColor VIPalette::getColor(const QString& name)
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

void VIPalette::setColor(const QString& name, const QColor& color)
{
	if (ColorMap.contains(name)) {
		ColorMap.remove(name);
		ColorMap.insert(name, color);
		emit colorChanged(name, color);
		return;
	}
	ColorMap.insert(name, color);
}

void VIPalette::setColor(DefaultColorName colorName, const QColor& color)
{
	setColor(getDefaultColorName(colorName), color);
}

QString VIPalette::getDefaultColorName(DefaultColorName colorName)
{
	//We think that it is not necessary to give default color a explicit name.
	return QString("DefaultColorName_" + QString::number((int)colorName)) + "";
}

/*
VIPaletteGroup
*/
def_init VIPaletteGroup::VIPaletteGroup() :VIObject() {
	VI_Singleton_Init;
	CurrentPalette = VI_NULLPTR;
	ChangePaletteUseAnimation = true;
	ChangeAnimationBehavior = new private_VIPaletteChangeAnimationBehavior(this);
	ChangeAnimationBehavior->setGroup(this);
	ChangeAnimationBehavior->setDuration(1000);
	this->addPalette("Default", VIColorMap());
	this->setColor(VIPalette::DefaultColorName::Foreground, QColor(253, 114, 255)); //Purple
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

void VIPaletteGroup::addPalette(const QString& name, VIPalette* palette) {
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

void VIPaletteGroup::setColorToPalette(const QString& paletteName, VIPalette::DefaultColorName colorName, const QColor& color) {
	if (PaletteMap.contains(paletteName)) {
		PaletteMap.value(paletteName)->setColor(colorName, color);
	}
}

void VIPaletteGroup::onPaletteChanged(const QString& raw, const QString& cur) {
	if (ChangePaletteUseAnimation) {
		if (PaletteMap.contains(raw) && PaletteMap.contains(cur)) {
			ChangeAnimationBehavior->setColorMap(PaletteMap.value(raw)->getColorMap(), PaletteMap.value(cur)->getColorMap());
			ChangeAnimationBehavior->setTargetPaletteName(cur);
			ChangeAnimationBehavior->start();
		}
	}
	else {
		emit paletteChanged(cur);
	}
}

/*
private_VIPaletteChangeAnimationBehavior
此类按如下方式工作：
1. 获取更换前的Palette对象和待更换的Palette对象
2. 从更换前的Palette对象中获取颜色映射表，再从待更换的Palette对象中缓存最终颜色映射表，作差得到delta颜色映射表
3. 将每刻的delta结果直接设到待更换的Palette对象中，然后发出paletteChanged信号，使用户可以在此信号中更新界面
4. 当动画结束时，将待更换的Palette对象的颜色映射表设为最终的颜色映射表
*/
def_init private_VIPaletteChangeAnimationBehavior::private_VIPaletteChangeAnimationBehavior(VIPaletteGroup* parent)
	:VIAnimationBehavior(parent) {
	Group = parent;
}

void private_VIPaletteChangeAnimationBehavior::setColorMap(const VIColorMap& raw, const VIColorMap& target) {
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

void private_VIPaletteChangeAnimationBehavior::onStart() HalfVirtual;
void private_VIPaletteChangeAnimationBehavior::onTick() {
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
void private_VIPaletteChangeAnimationBehavior::onStop() {
	Group->PaletteMap[TargetPaletteName]->setColorMap(CurrentColorMap);
}