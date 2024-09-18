#pragma once
#include "VIMacro.h"
#include <chrono>
#include <limits>
using VISecond = double; 
using VIMilliSecond = double;
using VIMicroSecond = long long;
using VINanoSecond = long long;

using STD_TimePoint = std::chrono::system_clock::time_point;
using VITimePoint = STD_TimePoint;
#define STD_clock_now std::chrono::system_clock::now
#define STD_Nano_duration(current, before) (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(current.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::nanoseconds>(before.time_since_epoch()).count())
#define STD_Milli_duration(current, before) (float)(std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::milliseconds>(before.time_since_epoch()).count())
#define VIMilliSecond_MAX 9223372036854.775807

#define Public_
#define Private_
#define Protected_