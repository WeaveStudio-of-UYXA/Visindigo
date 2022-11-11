#pragma once
#include <QtCore>
static QMutex VIJSMutex;
static QWaitCondition VIJSWait;

#define VIJSHostWait VIJSWait.wait(&VIJSMutex)
#define VIJSHostWake VIJSWait.wakeAll()
namespace JSVIAPI
{
	namespace GUI
	{
		class Host;
		class VIText :public QObject
		{
			Q_OBJECT
		private:
			QString TEXT;
			int MSPT;
			int MSW;
		public slots:
			void setText(QString text) {
				TEXT = text;
			}
			void setSpeed(int MsPT) {
				MSPT = MsPT;
			}
			void setWait(int MsW) {
				MSW = MsW;
			}
		};
		class VIPicture;
		class VISound;
		class VIBranch;
		class VIChara :public QObject
		{
			Q_OBJECT
		public:
			QString Name;
			QString DisplayName;
			Host* Manager;
			VIChara(QString name, QObject* parent = Q_NULLPTR) :QObject(parent) {
				Name = name;
				DisplayName = name;
			}
		public slots:
			VIChara* displayWith(QString displayname) {
				DisplayName = displayname;
				return this;
			}
			void say(QString text, int MsPT, int MsW);
		};
		class Host :public QObject
		{
			Q_OBJECT
		signals:
			void setDisplayName(QString);
			void setText(QString);
			void setFreeText(QString);
			void SsetWindowTitle(QString);
		public:
			QList<VIChara*> CharaList;
			Host(QObject* parent = Q_NULLPTR) :QObject(parent) {

			}
		public slots:
			VIChara* buildChara(QString name) {
				VIChara* Chara = new VIChara(name, this);
				CharaList.append(Chara);
				return Chara;
			}
			void setWindowTitle(QString title) {
				emit SsetWindowTitle(title);
			}
			void debug(QString info) {
				qDebug() << info;
			}
		};
	}
}