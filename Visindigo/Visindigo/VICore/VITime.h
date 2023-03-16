/*
Visindigo->VICore->VITime
此文档提供涉及时间管理的对象
*/
#pragma once
#include "macro/VIMarco.h"
#include "macro/VITime_m.h"
#include "VIUnit.h"

class VITime :public QObject
{
	Q_OBJECT;
	_Public VITimePoint Last;
	_Private bool isInit = true;
	_Public def_init VITime() { Last = STD_clock_now(); };
	_Public static VITimePoint getTimePointNow() { return STD_clock_now(); };
	_Public static VINanoSecond getNanoSecondNow() { return STD_clock_now().time_since_epoch().count(); };
	_Public static VIMilliSecond getMilliSecondNow() { return STD_clock_now().time_since_epoch().count() / 1000000.0; };
	_Public VINanoSecond getNanoDuration() { 
		if (isInit) {
			Last = STD_clock_now();
			isInit = false;
		}
		VITimePoint n = VITime::getTimePointNow();
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
		return STD_Nano_duration(VITime::getTimePointNow(), before);
	}
	_Public static VIMilliSecond getMilliDuration(VITimePoint before, VITimePoint after) {
		return STD_Milli_duration(after, before);
	}
	_Public static VIMilliSecond getMilliDuration(VITimePoint before) {
		return STD_Milli_duration(VITime::getTimePointNow(), before);
	}
};

