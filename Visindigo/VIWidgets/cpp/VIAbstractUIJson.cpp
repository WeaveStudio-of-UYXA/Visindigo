#pragma once
#include "../VIUJ.h"
#include "../VIUJWidgetBinder.h"
/*
VIAbstractUJParser
*/
QWidget* VIAbstractUJParser::preOnJson(const QJsonObject & jsonObj)
{
	QWidget* cuWidget = onJson(jsonObj);
	if (cuWidget == nullptr) {
		qDebug() << "VIAbstractUJParser::preOnJson: widget is null";
		return nullptr;
	}
	else {
		if (jsonObj.contains("Name")) {
			cuWidget->setObjectName(jsonObj["Name"].toString());
			qDebug() << "VIAbstractUJParser::preOnJson: set name to " << jsonObj["Name"].toString();
		}
		else {
			qDebug() << "VIAbstractUJParser::preOnJson: no name";
			if (CurrentWidgetStack.isEmpty()) {
				cuWidget->setObjectName("Root");
			}
			else {
				cuWidget->setObjectName(QString(CurrentWidgetStack.top()->children().length()));
			}
		}
		
		if (jsonObj.contains("Children")) {
			CurrentWidgetStack.push(cuWidget);
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
					qDebug() << "VIAbstractUJParser::preOnJson: child has no type, can not parse";
				}
			}
			CurrentWidgetStack.pop();
		}
		return cuWidget;
	}
}

/*
VIUIJsonParserHost
*/

void VIUIJsonParserHost::addUIJsonParser(VIAbstractUJParser* uiJson) {
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

VIAbstractUJParser* VIUIJsonParserHost::getUIJsonParser(const QString& typeName) {
	if (UIJsonMap.contains(typeName)) {
		VIConsole::inSuccessStyle(getLogPrefix() + "getUIJsonParser: " + typeName + " success");
		return UIJsonMap[typeName];
	}
	else {
		qDebug() << "VIUIJsonParserHost::getUIJsonParser: uiJson type name is not in map";
		return nullptr;
	}
}

void VIUIJsonParserHost::addUJWidgetBinder(VIUJWidgetBinder* ujWidgetBinder) {
	if (ujWidgetBinder == nullptr) {
		qDebug() << "VIUIJsonParserHost::addUJWidgetBinder: ujWidgetBinder is null";
		return;
	}
	if (UJWidgetBinderMap.contains(ujWidgetBinder->getTargetInstanceName())) {
		qDebug() << "VIUIJsonParserHost::addUJWidgetBinder: ujWidgetBinder type name is already in map";
		return;
	}
	UJWidgetBinderMap.insert(ujWidgetBinder->getTargetInstanceName(), ujWidgetBinder);
}

VIUJWidgetBinder* VIUIJsonParserHost::getUJWidgetBinder(const QString& targetInstanceName) {
	if (UJWidgetBinderMap.contains(targetInstanceName)) {
		VIConsole::inSuccessStyle(getLogPrefix() + "getUJWidgetBinder: " + targetInstanceName + " success");
		return UJWidgetBinderMap[targetInstanceName];
	}
	else {
		qDebug() << "VIUIJsonParserHost::getUJWidgetBinder: ujWidgetBinder type name is not in map";
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
		QWidget* cuWidget = UIJsonMap[type]->preOnJson(json);
		for (auto i = UJWidgetBinderMap.begin(); i != UJWidgetBinderMap.end(); i++) {
			qDebug()<<i.key();
			QWidget* Instance = findInstance(cuWidget, i.key());
			i.value()->setMaster(Instance);
		}
		return cuWidget;
	}
	else {
		qDebug() << "VIUIJsonParserHost::parse: uiJson type name is not in map";
		return nullptr;
	}
}

QWidget* VIUIJsonParserHost::findInstance(QWidget* root, const QString& instanceName) {
	QStringList instanceNameList = instanceName.split(".");
	if (instanceNameList.length() == 0) {
		qDebug() << "VIUIJsonParserHost::findInstance: instanceName is empty";
		return nullptr;
	}
	if (instanceNameList[0] != root->objectName()) {
		qDebug() << "VIUIJsonParserHost::findInstance: instanceName is not in root";
		return nullptr;
	}
	instanceNameList.removeFirst();
	QWidget* cuWidget = root;
	for (int i = 0; i < instanceNameList.length(); i++) {
		QObjectList children = cuWidget->children();
		bool isFind = false;
		for (int j = 0; j < children.length(); j++) {
			if (children[j]->objectName() == instanceNameList[i]) {
				cuWidget = (QWidget*)children[j];
				isFind = true;
				break;
			}
		}
		if (!isFind) {
			qDebug() << "VIUIJsonParserHost::findInstance: instanceName is not in root";
			return nullptr;
		}
	}
	return cuWidget;
}