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
	public:
		enum class ResourceMode {
			Pixmap = 0,
			Model = 1,
		};
	private:
		QString Name;
		QString ResourcePath;
		QMap<QString, QImage> ImageList;
	public:
		Q_INVOKABLE VIChara(QString name, QObject* parent = Q_NULLPTR) :QObject(parent) {
			this->setResourcePath("./Resource/Chara/" + name);
			this->Name = name;
		}
	public slots:
		QString getName() {
			return this->Name;
		}
		void setResourcePath(QString resourcePath) {
			this->ResourcePath = VIJSGlobal::getAbsolutePathOf(resourcePath);
		}
		QStringList loadPicture() {
			QString Path = this->ResourcePath + "/Picture";
			QDir dir(Path);
			dir.setNameFilters({"*.png"});
			QFileInfoList list = dir.entryInfoList();
			for ( auto i = list.begin(); i != list.end(); i++) {
				QString fileName = (* i).fileName();
				QString filePath = (* i).filePath();
				QImage image(filePath);
				this->ImageList.insert(fileName, image);
			}
		}
	};
}