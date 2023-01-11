#pragma once
#include<QtCore>
#include<QtWidgets>
#include <chrono>
#include "../../../CommonEdit/CECore/CEMacro.h"
typedef double VIMilliSecond;
typedef long long VINanoSecond;
typedef double VISecond;
typedef std::chrono::system_clock::time_point STD_TimePoint;

#define STD_clock_now std::chrono::system_clock::now
#define STD_Nano_duration(current, before) (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(current.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::nanoseconds>(before.time_since_epoch()).count())
#define STD_Milli_duration(current, before) (float)(std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::milliseconds>(before.time_since_epoch()).count())

#define gBEHAVIOR VIGeneralBehaviorHost::VIGeneralBehaviorHostInstance

//说实话，BIND，包括延伸到VIJS的反射的那一套玩意在内，其设计上算是非常失败
//但是我也不知道怎么改了
//下面这部分是VIGuiAnimation的宏，等有时间再说改的事情。
#define INIT (QWidget* parent = Q_NULLPTR) :VIAnimationEvent(parent) {} void init()
#define BIND(objP1,signal,objP2,slot) connect(objP1,signal,objP2,slot,Qt::BlockingQueuedConnection)
#define PROTECT ProcessMutex.lock();
#define RELEASE ProcessMutex.unlock();
#define EVENT void event()

