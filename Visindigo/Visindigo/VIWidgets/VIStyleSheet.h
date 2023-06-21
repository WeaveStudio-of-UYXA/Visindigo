#pragma once
#include "../VICore/VICore.h"


typedef QMap<QString, QColor> VIColorMap;

class VIColorPalette : public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void PaletteChanged();
	_Private VIColorMap* CurrentPalette;
	_Private QString CurrentPaletteName;
	_Private QMap<QString, VIColorMap> PaletteMap;
	_Public def_init VIColorPalette(VISuper* parent = VI_NULLPTR) :VIObject(parent) {
		CurrentPalette = VI_NULLPTR;
	}
	_Public void createPalette(const QString& name) {
		if (!PaletteMap.contains(name)) {
			PaletteMap.insert(name, VIColorMap());
		}
	}
	_Public void addPalette(const QString& name, const VIColorMap& palette) {
		if (!PaletteMap.contains(name)) {
			PaletteMap.insert(name, palette);
		}
	}
	_Public void addColorWithNameTo(const QString& name, const QColor& color, const QString& palette) {
		if (!PaletteMap.contains(palette)) {
			PaletteMap.insert(palette, VIColorMap());
		}
		if (!PaletteMap[palette].contains(name)) {
			PaletteMap[palette].insert(name, color);
		}
	}
	_Public void changeColorWithNameIn(const QString& name, const QColor& color, const QString& palette) {
		if (PaletteMap.contains(palette)) {
			if (PaletteMap[palette].contains(name)) {
				PaletteMap[palette][name] = color;
				emit PaletteChanged();
			}
		}
	}
	_Slot void changeCurrentPalette(const QString& name) {
		if (PaletteMap.contains(name)) {
			CurrentPalette = &PaletteMap[name];
			CurrentPaletteName = name;
			emit PaletteChanged();
		}
	}
	_Public QColor getColorWithName(const QString& name, const QString& paletteName = "") {
		if (paletteName != "") {
			if (PaletteMap.contains(paletteName)) {
				if (PaletteMap[paletteName].contains(name)) {
					return PaletteMap[paletteName].value(name);
				}
			}
			return QColor();
		}
		if (CurrentPalette == VI_NULLPTR) {
			if (PaletteMap.contains("default")) {
				if (PaletteMap["default"].contains(name)) {
					return PaletteMap["default"].value(name);
				}
			}
			return QColor();
		}
		if (CurrentPalette->contains(name)) {
			return CurrentPalette->value(name);
		}
		return QColor();
	}
	_Public QString getCurrentPaletteName() {
		return CurrentPaletteName;
	}
	_Public static QString toRGBStr(const QColor& color) {
		return QString("rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue());
	}
	_Public static QString toRGBAStr(const QColor& color) {
		return QString("rgba(%1,%2,%3,%4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
	}
	_Public static bool isColorLight(const QColor& color) {
		//Microsoft recommendation
		//see https://learn.microsoft.com/zh-cn/windows/apps/desktop/modernize/apply-windows-themes
		return (((5 * color.green()) + (2 * color.red()) + color.blue()) > (8 * 128));
	}
};

class VIStyleSheetManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QWidget* Master;
	_Private QMap<QString, QString> StyleSheeMap;
	_Private QString CurrentStyleSheetName;
	_Public VIColorPalette* Palette;
	_Public def_init VIStyleSheetManager(QWidget* master, VIColorPalette* palette = VI_NULLPTR) :VIObject(master) {
		Master = master;
		Palette = palette;
		if (Palette != VI_NULLPTR) {
			connect(Palette, &VIColorPalette::PaletteChanged, this, &VIStyleSheetManager::refreshStyleSheet);
		}
	}
	_Public void setPalette(VIColorPalette* palette) {
		Palette = palette;
		if (Palette != VI_NULLPTR) {
			connect(Palette, &VIColorPalette::PaletteChanged, this, &VIStyleSheetManager::refreshStyleSheet);
		}
	}
	_Public void addStyleSheet(const QString& name, const QString& styleSheet) {
		StyleSheeMap[name] = styleSheet;
	}
	_Public void applyStyleSheet(const QString& name) {
		if (StyleSheeMap.contains(name)) {
			QString ss = VISSExp_PATH(VISSExp_AUTOPR(StyleSheeMap[name], Master));
			if (Palette != VI_NULLPTR) {
				ss = VISSExp_COLOR(ss, Palette);
			}
			Master->setStyleSheet(ss);
			CurrentStyleSheetName = name;
		}
	}
	_Slot void refreshStyleSheet() {
		if (StyleSheeMap.contains(CurrentStyleSheetName)) {
			QString ss = VISSExp_PATH(VISSExp_AUTOPR(StyleSheeMap[CurrentStyleSheetName], Master));
			if (Palette != VI_NULLPTR) {
				ss = VISSExp_COLOR(ss, Palette);
			}
			Master->setStyleSheet(ss);
		}
	}
	_Public static QString VISSExp_AUTOPR(QString raw, QWidget* master) {
		while (true) {
			if (raw.contains("AUTO_") && raw.contains("_PR")) {
				int Index_b = raw.indexOf("AUTO_");
				int Index_e = raw.indexOf("_PR");
				QString pr = raw.mid(Index_b + 5, Index_e - Index_b - 5);
				raw.replace("AUTO_" + pr + "_PR", QString::number((int)(pr.toFloat() * master->height() / 100)) + "px");
			}
			else {
				break;
			}
		}
		return raw;
	}
	_Public static QString VISSExp_PATH(QString raw) {
		raw.replace(":EXEPATH", VIDocument::getApplicationsPath());
		//raw.replace(":PROJECTPATH", VIDocument::getProjectPath());
		raw.replace(":WORKPATH", VIDocument::getWorkingPath());
		return raw;
	}
	_Public static QString VISSExp_COLOR(QString raw, VIColorPalette* palette) {
		while (true) {
			if (raw.contains("CLR__") && raw.contains("__CLR")) {
				int Index_b = raw.indexOf("CLR__");
				int Index_e = raw.indexOf("__CLR");
				QString colorName = raw.mid(Index_b + 5, Index_e - Index_b - 5);
				raw.replace("CLR__" + colorName + "__CLR", VIColorPalette::toRGBAStr(palette->getColorWithName(colorName)));
			}
			else {
				break;
			}
		}
		return raw;
	}
	_Public static QString VISSExp_COLOR(QString raw, VIColorMap& map) {
		while (true) {
			if (raw.contains("CLR__") && raw.contains("__CLR")) {
				int Index_b = raw.indexOf("CLR__");
				int Index_e = raw.indexOf("__CLR");
				QString colorName = raw.mid(Index_b + 5, Index_e - Index_b - 5);
				raw.replace("CLR__" + colorName + "__CLR", VIColorPalette::toRGBAStr(map[colorName]));
			}
			else {
				break;
			}
		}
		return raw;
	}
};

class private_VIColorChangeAnimationBehavior :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QColor BlackColor = QColor(0, 0, 0, 255);
	_Private QColor WhiteColor = QColor(255, 255, 255, 255);
	_Private QColor TargetColor;
	_Private QColor RawColor;
	_Private QColor CurrentColor;
	_Private VIColorPalette* Palette;
	_Private QString PaletteName;
	_Private QString ColorName;
	_Public def_init private_VIColorChangeAnimationBehavior(QWidget* parent) :VIAnimationBehavior(parent) {
	}
	_Public void setTargetColor(QColor color) {
		TargetColor = color;
	}
	_Public void setPalette(VIColorPalette* palette) {
		Palette = palette;
	}
	_Public void setColorName(QString name) {
		ColorName = name;
	}
	_Public void setPaletteName(QString name) {
		PaletteName = name;
	}
	_Public void onActive()override {
		RawColor = Palette->getColorWithName(ColorName, PaletteName);
	}
	_Public void onTick()override {
		CurrentColor.setRed(RawColor.red() + (TargetColor.red() - RawColor.red()) * Duration->getPercent());
		CurrentColor.setGreen(RawColor.green() + (TargetColor.green() - RawColor.green()) * Duration->getPercent());
		CurrentColor.setBlue(RawColor.blue() + (TargetColor.blue() - RawColor.blue()) * Duration->getPercent());
		CurrentColor.setAlpha(RawColor.alpha() + (TargetColor.alpha() - RawColor.alpha()) * Duration->getPercent());
		Palette->changeColorWithNameIn(ColorName, CurrentColor, PaletteName);
	}
	_Public void onPassive()override {
		Palette->changeColorWithNameIn(ColorName, TargetColor, PaletteName);
	}
};
