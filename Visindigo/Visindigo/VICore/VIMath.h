#pragma once
#include <QtCore>

class VIMath :public QObject
{
public:
	struct VIVector2 {
		float x;
		float y;
	};
	typedef QList<VIVector2> VI2DMatrix;
	static VI2DMatrix getBesselCoefficient(VI2DMatrix PointMat) {
		VI2DMatrix ret;
		int n = PointMat.length() - 1;
		VIVector2 vec;
		int m = 0;
		for (auto i = PointMat.begin(); i != PointMat.end(); i++) {
			vec.x = i->x * Combination(n, m);
			vec.y = i->y * Combination(n, m);
			ret.append(vec);
			m++;
		}
		return ret;
	}
	static VIVector2 getBesselValue(VI2DMatrix BesselCoefficient, float p) {
		VIVector2 ret = {0, 0};
		int n = BesselCoefficient.length() - 1;
		int m = 0;
		for (auto i = BesselCoefficient.begin(); i != BesselCoefficient.end(); i++) {
			ret.x += i->x * qPow(p, m) * qPow(1 - p, n - m);
			ret.y += i->y * qPow(p, m) * qPow(1 - p, n - m);
			m++;
		}
		return ret;
	}
	static int Combination(int n, int m) {
		int ret = 1;
		for (int i = 0; i < m; i++) {
			ret *= (n - i);
		}
		for (int i = 0; i < m; i++) {
			ret /= (m - i);
		}
		return ret;
	}
	static int Permutation(int n, int m) {
		int ret = 1;
		for (int i = 0; i < m; i++) {
			ret *= (n - i);
		}
		return ret;
	}
};