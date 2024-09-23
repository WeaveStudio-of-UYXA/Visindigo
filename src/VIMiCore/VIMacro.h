#pragma once
#include "VIMiCoreCompileMacro.h"

#define VI_VERSION_MAJOR 2
#define VI_VERSION_MINOR 0
#define VI_VERSION_PATCH 0

#define _Public public:
#define _Private private:
#define _Protected protected:
#define _Slot public Q_SLOTS:
#define _Signal Q_SIGNALS:
#define PureVirtual = 0
#define HalfVirtual {}
#define Removed = delete
#define InitAsNull = Q_NULLPTR
#define InitAsZero = 0
#define InitAsNone = {}

#define def_init
#define def_del
#define def_copy
#define def_move
#define PASS
#define VI_NO_PARENT
