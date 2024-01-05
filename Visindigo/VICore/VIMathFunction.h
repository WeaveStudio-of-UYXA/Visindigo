#pragma once
#include "VIObject.h"

class VIMathFunction :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public enum Dimension { One, Two, Three };
	_Private Dimension dimension;
	_Private double Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	_Public void setXmin(double xmin) { Xmin = xmin; }
	_Public void setXmax(double xmax) { Xmax = xmax; }
	_Public void setYmin(double ymin) { Ymin = ymin; }
	_Public void setYmax(double ymax) { Ymax = ymax; }
	_Public void setZmin(double zmin) { Zmin = zmin; }
	_Public void setZmax(double zmax) { Zmax = zmax; }
	_Public void setXRange(double xmin, double xmax) { Xmin = xmin; Xmax = xmax; }
	_Public void setYRange(double ymin, double ymax) { Ymin = ymin; Ymax = ymax; }
	_Public void setZRange(double zmin, double zmax) { Zmin = zmin; Zmax = zmax; }
	_Public double xmin() { return Xmin; }
	_Public double xmax() { return Xmax; }
	_Public double ymin() { return Ymin; }
	_Public double ymax() { return Ymax; }
	_Public double zmin() { return Zmin; }
	_Public double zmax() { return Zmax; }
	_Public def_init VIMathFunction(Dimension dim) { dimension = dim; }
	_Public Dimension getDimension() { return dimension; }
	_Public virtual double f(double x) { return 0; }
	_Public virtual double f(double x, double y) { return 0; }
	_Public virtual double f(double x, double y, double z) { return 0; }
};
class VIMathFunctionTools :public VIObject
{
	_Public static double simpson(VIMathFunction* function, double infinitesimal = 0.00001) {
		switch (function->getDimension())
		{
		case VIMathFunction::One:
			return simpsonD1(function, infinitesimal);
		case VIMathFunction::Two:
			return simpsonD2(function, infinitesimal);
		case VIMathFunction::Three:
			return simpsonD3(function, infinitesimal);
		default:
			return 0;
		}
	}
	_Private static double simpsonD1(VIMathFunction* function, double infinitesimal = 0.00001);
	_Private static double simpsonD2(VIMathFunction* function, double infinitesimal = 0.00001) { return 0; }
	_Private static double simpsonD3(VIMathFunction* function, double infinitesimal = 0.00001) { return 0; }
	_Public static double root(VIMathFunction* function, double x0, double y0 = 0, double z0 = 0, double offset = 0, double infinitesimal = 0.00001) {
		switch (function->getDimension())
		{
		case VIMathFunction::One:
			return rootD1(function, x0, offset, infinitesimal);
		case VIMathFunction::Two:
			return rootD2(function, x0, y0, offset, infinitesimal);
		case VIMathFunction::Three:
			return rootD3(function, x0, y0, z0, offset, infinitesimal);
		default:
			return 0;
		}
	}
	_Private static double rootD1(VIMathFunction* function, double x0, double offset = 0, double infinitesimal = 0.00001);
	_Private static double rootD2(VIMathFunction* function, double x0, double y0 = 0, double offset = 0, double infinitesimal = 0.00001) { return 0; }
	_Private static double rootD3(VIMathFunction* function, double x0, double y0 = 0, double z0 = 0, double offset = 0, double infinitesimal = 0.00001) { return 0; }

};