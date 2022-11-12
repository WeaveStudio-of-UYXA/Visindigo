#pragma once
#include <QtCore>
namespace JsVI
{
	class VISystem :public QObject
	{
		Q_OBJECT
	public:
		VISystem(QObject* parent = Q_NULLPTR) :QObject(parent) {
		}
	public slots:
		void print(QString str) {
			qDebug() << str;
		}
		void exit(int code = 0) {
			qApp->exit(code);
		}
		void wait(int ms) {
			QThread::msleep(ms);
		}
	};
}