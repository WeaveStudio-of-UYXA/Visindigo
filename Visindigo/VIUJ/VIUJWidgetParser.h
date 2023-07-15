#pragma once
#include "VIUJAbstractParser.h"
#include "../VIWidgets/VIWidgets.h"

class VIUJParser_VIWidget : public VIUJAbstractParser
{
	_Public def_init VIUJParser_VIWidget(VIUJParserHost* host) :VIUJAbstractParser(host) {
		setTypeName("VIWidget");
	}
	_Public void onGeneralParameters(const QJsonObject& json, QWidget* widget) {
		if(json.contains("Title")) {
			widget->setWindowTitle(json["Title"].toString());
		}
		if (json.contains("Size")) {  
			QJsonArray size = json["Size"].toArray();
			widget->resize(size[0].toInt(), size[1].toInt());
		}
		if (json.contains("Layout")) {
			QString layoutName = json["Layout"].toString();
			if (layoutName == "H") {
				QHBoxLayout* layout = new QHBoxLayout();
				widget->setLayout(layout);
			}
			else if (layoutName == "V") {
				QVBoxLayout* layout = new QVBoxLayout();
				widget->setLayout(layout);
			}
		}
		if (json.contains("Name")) {
			widget->setObjectName(json["Name"].toString());
		}
		if (json.contains("StyleSheet")) {
			widget->setStyleSheet(json["StyleSheet"].toString());
		}
	}
	_Public virtual QWidget* onJson(const QJsonObject& json) override {
		QWidget* widget = new VIWidget();
		onGeneralParameters(json, widget);
		return widget;
	}
	_Public virtual void onNewChild(QWidget* child) override {
		if (getCurrentWidget()->layout()!=nullptr) {
			getCurrentWidget()->layout()->addWidget(child);
		}
	}
};

class VIUJParser_VILabel :public VIUJParser_VIWidget
{
	_Public def_init VIUJParser_VILabel(VIUJParserHost* host) :VIUJParser_VIWidget(host) {
		setTypeName("VILabel");
	}
	_Public virtual QWidget* onJson(const QJsonObject& json) override {
		QLabel* label = new VILabel();
		onGeneralParameters(json, label);
		if (json.contains("Text")) {
			label->setText(json["Text"].toString());
		}
		return label;
	}
};

class VIUJParser_VISwitchButton :public VIUJParser_VIWidget
{
	_Public def_init VIUJParser_VISwitchButton(VIUJParserHost* host) :VIUJParser_VIWidget(host) {
		setTypeName("VISwitchButton");
	}
	_Public virtual QWidget* onJson(const QJsonObject& json) override {
		VISwitchButton* label = new VISwitchButton();
		onGeneralParameters(json, label);
		return label;
	}
};