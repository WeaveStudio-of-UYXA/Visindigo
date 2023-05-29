#pragma once
#include <QtCore>
#include "VIBasicType.h"
#include "private/VIMacro.h"
class VIMath {
public:
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
