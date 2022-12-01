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
		void exit(int code = 0) {
			qApp->exit(code);
		}
		QString getSystemProductName() {
			return QSysInfo::prettyProductName();
		}
		void print(QString str) {
			qDebug() << str;
		}
		void wait(int ms) {
			QThread::msleep(ms);
		}
		QStringList argv() {
			return qApp->arguments();
		}
	};
}