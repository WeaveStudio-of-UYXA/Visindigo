#pragma once
#include "VIJSGlobal.h"
#include "JsVIBase.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
namespace JsVI
{
	class VIChara :public QObject
	{
		Q_OBJECT
	private:
		QString Name;
		QString DisplayName;
		QString ResourcePath;
		QMap<QString, QImage> ImageList;
	public:
		Q_INVOKABLE VIChara(QString name, QString displayName, QObject* parent = Q_NULLPTR) :QObject(parent) {
			this->setResourcePath("./Resource/Chara/" + name);
			this->Name = name;
			this->DisplayName = displayName;
		}
	public slots:
		QString getName() {
			return this->Name;
		}
		QString getDisplayName() {
			return this->DisplayName;
		}
		void setResourcePath(QString resourcePath) {
			this->ResourcePath = VIJSGlobal::getAbsolutePathOf(resourcePath);
		}
		QStringList loadPicture() {
			QString Path = this->ResourcePath + "/Picture";
			QDir dir(Path);
			dir.setNameFilters({ "*.png" });
			QFileInfoList list = dir.entryInfoList();
			for (auto i = list.begin(); i != list.end(); i++) {
				QString fileName = (*i).fileName();
				QString filePath = (*i).filePath();
				QImage image(filePath);
				this->ImageList.insert(fileName, image);
			}
			return this->ImageList.keys();
		}
	};
}