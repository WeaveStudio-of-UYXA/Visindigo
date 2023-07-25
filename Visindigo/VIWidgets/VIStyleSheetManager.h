#pragma once
#include "VIPalette.h"
struct VIStyleSheetData
{
	QString StyleSheet;
	bool HasDynamicSize;
	bool HasDynamicColor;
	QStringList DynamicSizeNames;
	QStringList DynamicColorNames;
};
class VIPublicAPI VIStyleSheetManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QHash<QString, VIStyleSheetData> StyleSheetData;
	_Private QWidget * MasterWidget;
	_Private VIPaletteGroup* PaletteGroup;
	VI_PrivateProperty(QString, CurrentStyleSheetName);
	_Public def_init VIStyleSheetManager(QWidget* MasterWidget);
	_Slot void refreshStyleSheet() {
		applyStyleSheet(CurrentStyleSheetName);
	}
	_Slot void onPaletteChanged(QString PaletteName) {
		refreshStyleSheet();
	}
	_Slot void onColorChanged(QString PaletteName, QString colorName, QColor color) {
		if (StyleSheetData.contains(CurrentStyleSheetName)) {
			VIStyleSheetData& data = StyleSheetData[CurrentStyleSheetName];
			if (data.HasDynamicColor&& data.DynamicColorNames.contains(colorName)) {
					refreshStyleSheet();
			}
		}
	}
	_Public void addStyleSheet(const QString& name, const QString& ss) {
		VIStyleSheetData data;
		data.StyleSheet = ss;
		data.DynamicSizeNames = hasDynamicSize(ss);
		data.DynamicColorNames = hasDynamicColor(ss);
		data.HasDynamicSize = data.DynamicSizeNames.size() > 0;
		data.HasDynamicColor = data.DynamicColorNames.size() > 0;
		StyleSheetData[name] = data;
	}
	_Public void applyStyleSheet(const QString& name) {
		if (StyleSheetData.contains(name)) {
			VIStyleSheetData& data = StyleSheetData[name];
			QString ss = data.StyleSheet;
			if (data.HasDynamicSize) {
				applyDynamicSize(&ss, data);
			}
			if (data.HasDynamicColor) {
				applyDynamicColor(&ss, data);
			}
			MasterWidget->setStyleSheet(ss);
			CurrentStyleSheetName = name;
		}
	}
	_Private void applyDynamicSize(QString* ss, VIStyleSheetData& data) {
		for (auto& name : data.DynamicSizeNames) {
			float value = QString(name).toFloat();
			value*=MasterWidget->height();
			QString px = QString::number(value) + "px";
			ss->replace("AUTO_" + name + "_PR", px);
		}
	}
	_Private void applyDynamicColor(QString* ss, VIStyleSheetData& data) {
		for (auto& name : data.DynamicColorNames) {
			QString color = VIColorTools::toRGBAString(PaletteGroup->getColor(name));
			ss->replace("AUTO_" + name + "_CLR", color);
		}
	}
	_Public static QStringList hasDynamicSize(const QString& ss) {
		int index_auto = 0;
		int index_pr = 0;
		QStringList rtn;
		while (true) {
			index_auto = ss.indexOf("AUTO_", index_auto);
			index_pr = ss.indexOf("_PR", index_pr);
			if (index_auto == -1 || index_pr == -1) {
				break;
			}
			QString colorName = ss.mid(index_auto + 5, index_pr - index_auto - 5);
			rtn << colorName;
			index_auto = index_pr;
			index_pr += 3;
		}
		return rtn;
	}
	_Public static QStringList hasDynamicColor(const QString& ss) {
		int index_auto = 0;
		int index_clr = 0;
		QStringList rtn;
		while (true) {
			index_auto = ss.indexOf("AUTO_", index_auto);
			index_clr = ss.indexOf("_CLR", index_clr);
			if (index_auto == -1 || index_clr == -1) {
				break;
			}
			QString colorName = ss.mid(index_auto + 5, index_clr - index_auto - 5);
			rtn << colorName;
			index_auto = index_clr;
			index_clr += 4;
		}
		return rtn;
	}
};
