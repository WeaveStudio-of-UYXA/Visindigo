#pragma once
#include "VIMacro.h"
#include <chrono>

typedef double VISecond;
typedef double VIMilliSecond;
typedef long long VIMicroSecond;
typedef long long VINanoSecond;

typedef std::chrono::system_clock::time_point STD_TimePoint;
typedef STD_TimePoint VITimePoint;
#define STD_clock_now std::chrono::system_clock::now
#define STD_Nano_duration(current, before) (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(current.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::nanoseconds>(before.time_since_epoch()).count())
#define STD_Milli_duration(current, before) (float)(std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::milliseconds>(before.time_since_epoch()).count())
