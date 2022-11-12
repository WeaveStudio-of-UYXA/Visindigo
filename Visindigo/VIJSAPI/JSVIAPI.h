/*
* 本文件内容危险！
* 只允许VIJSHost.h实例化本文件内的类，VIJSHostWake只允许其他外部调用
* 本文件假定所有操作都由VIJSHost线程进行，因此存在类似于sleep()之类的玩意，请勿自行使用
*/

#pragma once
#include <QtCore>
#include "../VIUI/MRW/GUI2D/VI2DGUI.h"
#include "../VIUI/MRW/VIGUI2D.h"

namespace JSVIAPI
{
	namespace System
	{
		class Host;
		class Host :public QObject
		{
			Q_OBJECT
		public:
			Host(QObject* parent = Q_NULLPTR):QObject(parent) {
				
			}
		public slots:
			void exit(int code) {
				QCoreApplication::exit(code);
			}
			void print(QString str) {
				qDebug() << str;
			}
			void sleep(int ms) {
				QThread::msleep(ms);
			}
		};
	}
	namespace GUI
	{
		class Host;

		class Host :public QObject
		{
			Q_OBJECT
		signals:
			void SsetWindowTitle(QString);
			void SshowFullScreen();
		public:
			Host(QObject* parent = Q_NULLPTR) :QObject(parent) {

			}
		public slots:
			void setWindowTitle(QString title) {
				emit SsetWindowTitle(title);
			}
			void showFullScreen() {
				emit SshowFullScreen();
			}
			void debug(QString info) {
				qDebug() << info;
			}
		};
	}
}