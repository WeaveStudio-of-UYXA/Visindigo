#include "VISystemBase.h"
void VIBase::VISystem_Glass::exit(int code) {
	qApp->exit(code);
}
QString VIBase::VISystem_Glass::getSystemProductName() {
	return QSysInfo::prettyProductName();
}
void VIBase::VISystem_Glass::print(QString str) {
	qDebug() << str;
}
void VIBase::VISystem_Glass::wait(int ms) {
	QThread::msleep(ms);
}
QStringList VIBase::VISystem_Glass::argv() {
	return qApp->arguments();
}