#pragma once
#include <QtCore>

#define NULLOBJECT nullptr

#define MemPool SPOLMemoryPool::Instance

#define MemPool_BaseList 3
#define MemPool_IntOffset 1
#define MemPool_IntPointer(index) MemPool_IntOffset + (index + 1) * MemPool_BaseList
#define MemPool_IsIntPoiner(pointer) pointer % MemPool_BaseList == MemPool_IntOffset
#define MemPool_IntIndex(pointer) (pointer - MemPool_IntOffset) / MemPool_BaseList - 1
#define MemPool_FloatOffset 2
#define MemPool_FloatPointer(index) MemPool_FloatOffset + (index + 1) * MemPool_BaseList
#define MemPool_IsFloatPoiner(pointer) pointer % MemPool_BaseList == MemPool_FloatOffset
#define MemPool_FloatIndex(pointer) (pointer - MemPool_FloatOffset) / MemPool_BaseList - 1
#define MemPool_StringOffset 3
#define MemPool_StringPointer(index) MemPool_StringOffset + (index + 1) * MemPool_BaseList
#define MemPool_IsStringPoiner(pointer) pointer % MemPool_StringOffset == 0
#define MemPool_StringIndex(pointer) (pointer - MemPool_FloatOffset) / MemPool_BaseList - 1