#pragma once
#include "private/VIDuration_m.h"
#include "private/VIMacro.h"
#include "VIObject.h"
/*
统一术语：
Duration: 持续时间
Elapse: 流逝时间
Remain: 剩余时间
VIBehaviorDuration使用纳秒管理时间
*/

class VIBehaviorDuration :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public ENUM PercentType{
		Linear,
		Nonlinear,
	};
	_Signal void timeout();
	VI_Property(VINanoSecond, Duration);
	VI_PrivateProperty(VINanoSecond, Elapse);
	VI_PrivateProperty(float, Percent);
	VI_PrivateFlag(Timeout);
	_Public def_init VIBehaviorDuration(VISuper* parent = Q_NULLPTR) : VIObject(parent) { Duration = 1; }
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

class VIDuration :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public VITimePoint Last;
	_Private bool isInit = true;
	_Public def_init VIDuration(VISuper* parent = VI_NULLPTR) :VIObject(parent) { Last = STD_clock_now(); };
	_Public static VITimePoint getTimePointNow() { return STD_clock_now(); };
	_Public static VINanoSecond getNanoSecondNow() { return STD_clock_now().time_since_epoch().count(); };
	_Public static VIMilliSecond getMilliSecondNow() { return STD_clock_now().time_since_epoch().count() / 1000000.0; };
	_Public VINanoSecond getNanoDuration() {
		if (isInit) {
			Last = STD_clock_now();
			isInit = false;
		}
		VITimePoint n = VIDuration::getTimePointNow();
		VINanoSecond d = STD_Nano_duration(n, Last);
		Last = n;
		return d;
	};
	_Public VIMilliSecond getMilliDuration() {
		VINanoSecond d = getNanoDuration();
		return (float)d / 1000000.0;
	};
	_Public static VINanoSecond getNanoDuration(VITimePoint before, VITimePoint after) {
		return STD_Nano_duration(after, before);
	}
	_Public static VINanoSecond getNanoDuration(VITimePoint before) {
		return STD_Nano_duration(VIDuration::getTimePointNow(), before);
	}
	_Public static VIMilliSecond getMilliDuration(VITimePoint before, VITimePoint after) {
		return STD_Milli_duration(after, before);
	}
	_Public static VIMilliSecond getMilliDuration(VITimePoint before) {
		return STD_Milli_duration(VIDuration::getTimePointNow(), before);
	}
};