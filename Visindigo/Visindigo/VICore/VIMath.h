#pragma once
#include <QtCore>
#include "private/VIMacro.h"
namespace VIMath {
	struct VIVector2
	{
		float x;
		float y;
	};
	struct VIVector3
	{
		float x;
		float y;
		float z;
	};
	struct VIVector4
	{
		float x;
		float y;
		float z;
		float w;
	};
	struct VIVector5
	{
		float x;
		float y;
		float z;
		float w;
		float u;
	};
	typedef float VIVector;
	typedef QList<VIVector> VIMatrix;
	typedef QList<VIVector2> VI2DMatrix;
	typedef QList<VIVector3> VI3DMatrix;
	typedef QList<VIVector4> VI4DMatrix;
}

class VIBessel :public QObject
{
public:
	static VIMath::VI2DMatrix getBesselCoefficient(VIMath::VI2DMatrix PointMat) {
		VIMath::VI2DMatrix ret;
		int n = PointMat.length() - 1;
		VIMath::VIVector2 vec;
		int m = 0;
		for (auto i = PointMat.begin(); i != PointMat.end(); i++) {
			vec.x = i->x * Combination(n, m);
			vec.y = i->y * Combination(n, m);
			ret.append(vec);
			m++;
		}
		return ret;
	}
	static VIMath::VIMatrix getBesselCoefficient(VIMath::VIMatrix PointMat) {
		VIMath::VIMatrix ret;
		int n = PointMat.length() - 1;
		int v;
		int m = 0;
		for (auto i = PointMat.begin(); i != PointMat.end(); i++) {
			v = (*i) * Combination(n, m);
			ret.append(v);
			m++;
		}
		return ret;
	}
	static VIMath::VIVector2 getBesselValue(VIMath::VI2DMatrix BesselCoefficient, float p) {
		VIMath::VIVector2 ret = { 0, 0 };
		int n = BesselCoefficient.length() - 1;
		int m = 0;
		for (auto i = BesselCoefficient.begin(); i != BesselCoefficient.end(); i++) {
			ret.x += i->x * qPow(p, m) * qPow(1 - p, n - m);
			ret.y += i->y * qPow(p, m) * qPow(1 - p, n - m);
			m++;
		}
		return ret;
	}
	static float getBesselValue(VIMath::VIMatrix BesselCoefficient, float p) {
		float ret = 0;
		int n = BesselCoefficient.length() - 1;
		int m = 0;
		for (auto i = BesselCoefficient.begin(); i != BesselCoefficient.end(); i++) {
			ret += (*i) * qPow(p, m) * qPow(1 - p, n - m);
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
