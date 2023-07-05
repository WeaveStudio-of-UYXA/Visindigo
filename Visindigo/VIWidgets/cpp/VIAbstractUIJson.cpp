#pragma once
#include "../VIAbstractUIJson.h"
/*
VIAbstractUIJsonParser
*/
QWidget* VIAbstractUIJsonParser::preOnJson(const QJsonObject & jsonObj)
{
	QWidget* cuWidget = onJson(jsonObj);
	if (cuWidget == nullptr) {
		return nullptr;
	}
	else {
		CurrentWidgetStack.push(cuWidget);
		if (jsonObj.contains("Children")) {
			QJsonArray children = jsonObj["Children"].toArray();
			for (int i = 0; i < children.size(); i++) {
				QJsonObject child = children[i].toObject();
				if (child.contains("Type")) {
					QString type = child["Type"].toString();
					QWidget* childWidget = Host->getUIJsonParser(type)->preOnJson(child);
					if (childWidget != nullptr) {
						childWidget->setParent(cuWidget);
						onNewChild(childWidget);
					}
				}
				else {
					qDebug() << "VIAbstractUIJsonParser::preOnJson: child has no type, can not parse";
				}
			}
		}
		CurrentWidgetStack.pop();
		return cuWidget;
	}
}

/*
VIUIJsonParserHost
*/

void VIUIJsonParserHost::addUIJsonParser(VIAbstractUIJsonParser* uiJson) {
	if (uiJson == nullptr) {
		qDebug() << "VIUIJsonParserHost::addUIJsonParser: uiJson is null";
		return;
	}
	if (UIJsonMap.contains(uiJson->getTypeName())) {
		qDebug() << "VIUIJsonParserHost::addUIJsonParser: uiJson type name is already in map";
		return;
	}
	UIJsonMap.insert(uiJson->getTypeName(), uiJson);
}

VIAbstractUIJsonParser* VIUIJsonParserHost::getUIJsonParser(const QString& typeName) {
	if (UIJsonMap.contains(typeName)) {
		VIConsole::inSuccessStyle(getLogPrefix() + "getUIJsonParser: " + typeName + " success");
		return UIJsonMap[typeName];
	}
	else {
		qDebug() << "VIUIJsonParserHost::getUIJsonParser: uiJson type name is not in map";
		return nullptr;
	}
}
QWidget* VIUIJsonParserHost::parse(const QString& fileName) {
	if (!QFile::exists(fileName)) {
		qDebug() << "VIUIJsonParserHost::parse: file not exist";
		return nullptr;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "VIUIJsonParserHost::parse: file open failed";
		return nullptr;
	}
	QTextStream in(&file);
	in.setCodec("utf-8");
	QString jsonStr = in.readAll();
	file.close();
	QJsonParseError jsonError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError) {
		qDebug() << "VIUIJsonParserHost::parse: json parse error";
		return nullptr;
	}
	if (!jsonDoc.isObject()) {
		qDebug() << "VIUIJsonParserHost::parse: json is not object";
		return nullptr;
	}
	QJsonObject json = jsonDoc.object();
	return parse(json);
}
QWidget* VIUIJsonParserHost::parse(const QJsonObject& json) {
	if (!json.contains("Type")) {
		qDebug() << "VIUIJsonParserHost::parse: no type, can not parse";
		return nullptr;
	}
	QString type = json["Type"].toString();
	if (UIJsonMap.contains(type)) {
		return UIJsonMap[type]->preOnJson(json);
	}
	else {
		qDebug() << "VIUIJsonParserHost::parse: uiJson type name is not in map";
		return nullptr;
	}
}