#pragma once
typedef int VISoundServiceKey;

#define getOuterServiceKeyWithIndex(index) getServiceKey() * (index+1)
#define keyIsTargetPlayer(key, index) at(i)->getServiceKey() == key / (index+1)