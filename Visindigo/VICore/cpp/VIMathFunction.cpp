#include "../VIMathFunction.h"

double VIMathFunctionTools::simpsonD1(VIMathFunction* function, double infinitesimal) {
	double rt1 = 0, rt2 = 0;
	double length = function->xmax() - function->xmin();
	rt1 = function->f(function->xmin()) * length;
	QVector<double> x_last = { function->xmin()};
	while (true) {
		length = length / 2;
		QVector<double> x_new;
		for (auto i : x_last) {
			x_new.append(i + length);
		}
		rt2 = rt1 * 0.5;
		for (auto i : x_new) {
			rt2 += function->f(i) * length;
		}
		if (qAbs(rt1 - rt2) <= infinitesimal) {
			return rt2;
		}
		else {
			rt1 = rt2;
			x_last.append(x_new);
		}
	}
}