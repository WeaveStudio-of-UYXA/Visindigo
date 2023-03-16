#pragma once
#include "VITime.h"
#include "VIMath.h"
/*
ͳһ���
Duration: ����ʱ��
Elapse: ����ʱ��
Remain: ʣ��ʱ��
VIBehaviorDurationʹ���������ʱ��
*/
class VIBehaviorDuration :public QObject
{
	Q_OBJECT;
	_Public ENUM PercentType{
		Linear,
		Nonlinear,
	};
	_Signal void timeout();
	VI_Property(VINanoSecond, Duration);
	VI_PrivateProperty(VINanoSecond, Elapse);
	VI_PrivateProperty(float, Percent);
	VI_PrivateFlag(Timeout);
	_Public def_init VIBehaviorDuration(QObject* parent = Q_NULLPTR) : QObject(parent) { Duration = 1; }
	_Public void initDuration() {
		Timeout = false;
		Elapse = 0;
		Percent = 0;
	}
	_Slot void addTime(VINanoSecond time) {
		Elapse += time;
		qDebug() << Elapse;
		Percent = Elapse / Duration;
		if (Elapse >= Duration) {
			Timeout = true;
			emit timeout();
		}
	}
};