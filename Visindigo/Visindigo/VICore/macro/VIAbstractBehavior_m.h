#pragma once
#include<QtCore>
#include<QtWidgets>
#include <chrono>
#include "VIMarco.h"
#include "VIDuration_m.h"

//#define gBEHAVIOR VIGeneralBehaviorHost::VIGeneralBehaviorHostInstance
//#define mBEHAVIOR VIMainBehaviorHost::VIMainBehaviorHostInstance
//说实话，BIND，包括延伸到VIJS的反射的那一套玩意在内，其设计上算是非常失败
//但是我也不知道怎么改了
//下面这部分是VIGuiAnimation的宏，等有时间再说改的事情。
#define INIT (QWidget* parent = Q_NULLPTR) :VIAnimationEvent(parent) {} void init()
#define BIND(objP1,signal,objP2,slot) connect(objP1,signal,objP2,slot,Qt::BlockingQueuedConnection)
#define PROTECT ProcessMutex.lock();
#define RELEASE ProcessMutex.unlock();
#define EVENT void event()

