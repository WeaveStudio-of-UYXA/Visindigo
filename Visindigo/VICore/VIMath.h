#pragma once
#include <QtCore>
#include "private/VIMacro.h"

class VIMath {
	VI_STATIC_CLASS(VIMath);
public:
	static float PI;
	static int combination(int n, int m) {
		int ret = 1;
		for (int i = 0; i < m; i++) {
			ret *= (n - i);
		}
		for (int i = 0; i < m; i++) {
			ret /= (m - i);
		}
		return ret;
	}
	static int permutation(int n, int m) {
		int ret = 1;
		for (int i = 0; i < m; i++) {
			ret *= (n - i);
		}
		return ret;
	}
	
};

class VICommonMapping {
	VI_STATIC_CLASS(VICommonMapping);
	_Public static double sin_0_1(double percent) {
		return (qSin(-VIMath::PI / 2 + VIMath::PI * percent) + 1.0) / 2.0;
	}
	_Public static double sin_0_1_0(double percent) {
		return qSin(percent * VIMath::PI);
	}
};