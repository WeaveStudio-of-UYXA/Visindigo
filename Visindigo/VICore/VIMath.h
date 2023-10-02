#pragma once
#include <QtCore>
#include "private/VIMacro.h"

namespace VIMath {
	const float PI = 3.141592653;
	int combination(int n, int m);
	int permutation(int n, int m);
}

class VIPublicAPI VICommonMapping {
	VI_STATIC_CLASS(VICommonMapping);
	_Public static double sin_0_1(double percent) {
		return (qSin(-VIMath::PI / 2 + VIMath::PI * percent) + 1.0) / 2.0;
	}
	_Public static double cos_1_n1(double percent) {
		return qCos(percent * VIMath::PI);
	}
	_Public static double sin2_0_1(double percent) {
		return qPow(sin_0_1(percent), 2);
	}
	_Public static double sin_0_1_0(double percent) {
		return qSin(percent * VIMath::PI);
	}
	_Public static double simpleTransformation(double percent, Visindigo::SimpleTransformation t = Visindigo::Line) {
		switch (t) {
		case Visindigo::Line:
			return percent;
		case Visindigo::Exponential:
			return (qExp(percent) - 1) / (qExp(1) - 1);
		case Visindigo::Logarithmic:
			return qLn(percent * (qExp(1) - 1) + 1);
		case Visindigo::Sqrt:
			return qSqrt(percent);
		case Visindigo::Square:
			return qPow(percent, 2);
		case Visindigo::Invert:
			return 1 - percent;
		case Visindigo::InvertExponential:
			return 1 - (qExp(percent) - 1) / (qExp(1) - 1);
		case Visindigo::InvertLogarithmic:
			return 1 - qLn(percent * (qExp(1) - 1) + 1);
		case Visindigo::InvertSqrt:
			return 1 - qSqrt(percent);
		case Visindigo::InvertSquare:
			return 1 - qPow(percent, 2);
		default:
			return percent;
		}
	}
};