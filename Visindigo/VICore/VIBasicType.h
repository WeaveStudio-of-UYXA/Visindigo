#pragma once
#include "VIObject.h"
#include "VIConsole.h"
#include "VIException.h"
#include "VIMath.h"
/*
* Notice: All the code in this file is not tested.
* Please do not use it directly.
*/
//此项目控制VICoordinate的浮点置信度
#define VI_COORDINATE_CONFIDENCE 0.0000000001
class VIPrivateAPI VICoordinate
{
	friend class VICoordinate;
	_Public enum class Dimension {
		D1 = 1,
		D2 = 2,
		D3 = 3,
		D4 = 4
	};
	VI_Property(double, X);
	VI_Property(double, Y);
	VI_Property(double, Z);
	VI_Property(double, W);
	VI_Property(Dimension, Dim);
	_Public def_init VICoordinate(Dimension d, double x, double y = 0, double z = 0, double w = 0) {
		Dim = d;
		X = x; Y = y; Z = z; W = w;
	};
	_Public def_init VICoordinate() {
		Dim = Dimension::D1;
		X = 0; Y = 0; Z = 0; W = 0;
	};
	_Public def_copy VICoordinate(const VICoordinate& c) {
		Dim = c.Dim;
		X = c.X; Y = c.Y; Z = c.Z; W = c.W;
	};
	_Public VICoordinate operator=(const VICoordinate& c) {
		Dim = c.Dim;
		X = c.X; Y = c.Y; Z = c.Z; W = c.W;
		return *this;
	};
	_Public double getDistanceTo(const VICoordinate& c) {
		if (Dim != c.Dim) {
			throw VIDimensionError("VICoordinates::getDistanceTo() only allows coordinates of the same dimension");
		}
		switch (Dim)
		{
		case VICoordinate::Dimension::D1:
			return qAbs(X - c.X);
		case VICoordinate::Dimension::D2:
			return qSqrt(qPow(X - c.X, 2) + qPow(Y - c.Y, 2));
		case VICoordinate::Dimension::D3:
			return qSqrt(qPow(X - c.X, 2) + qPow(Y - c.Y, 2) + qPow(Z - c.Z, 2));
		case VICoordinate::Dimension::D4:
			return qSqrt(qPow(X - c.X, 2) + qPow(Y - c.Y, 2) + qPow(Z - c.Z, 2) + qPow(W - c.W, 2));
		}
	}
	_Public bool inSameDim(const VICoordinate& c) {
		return Dim == c.Dim;
	}
	_Public bool isSameVector(const VICoordinate& c) {
		if (Dim != c.Dim) return false;
		double rate = c.X / X;
		if (c.Y / Y - rate > VI_COORDINATE_CONFIDENCE) return false;
		if (c.Z / Z - rate > VI_COORDINATE_CONFIDENCE) return false;
		if (c.W / W - rate > VI_COORDINATE_CONFIDENCE) return false;
		return true;
	}
	_Public bool operator== (const VICoordinate& c) {
		return Dim == c.Dim && X == c.X && Y == c.Y && Z == c.Z && W == c.W;
	}
	_Public bool operator!= (const VICoordinate& c) {
		return Dim != c.Dim || X != c.X || Y != c.Y || Z != c.Z || W != c.W;
	}
	_Public VICoordinate operator+ (const VICoordinate& c) {
		if (Dim != c.Dim) {
			throw VIDimensionError("VICoordinates::operator+() only allows coordinates of the same dimension");
		}
		VICoordinate rtn(Dim, 0, 0, 0, 0);
		rtn.X = X + c.X;
		rtn.Y = Y + c.Y;
		rtn.Z = Z + c.Z;
		rtn.W = W + c.W;
		return rtn;
	}
	_Public VICoordinate operator- (const VICoordinate& c) {
		if (Dim != c.Dim) {
			throw VIDimensionError("VICoordinates::operator-() only allows coordinates of the same dimension");
		}
		VICoordinate rtn(Dim, 0, 0, 0, 0);
		rtn.X = X - c.X;
		rtn.Y = Y - c.Y;
		rtn.Z = Z - c.Z;
		rtn.W = W - c.W;
		return rtn;
	}
	_Public VICoordinate operator* (const double d) {
		VICoordinate rtn(Dim, 0, 0, 0, 0);
		rtn.X = X * d;
		rtn.Y = Y * d;
		rtn.Z = Z * d;
		rtn.W = W * d;
		return rtn;
	}
	_Public VICoordinate operator/ (const double d) {
		VICoordinate rtn(Dim, 0, 0, 0, 0);
		rtn.X = X / d;
		rtn.Y = Y / d;
		rtn.Z = Z / d;
		rtn.W = W / d;
		return rtn;
	}
};
typedef VICoordinate VI1DCoordinate;
typedef VICoordinate VI2DCoordinate;
typedef VICoordinate VI3DCoordinate;
typedef VICoordinate VI4DCoordinate;
#define VI1DCoor(x) VI1DCoordinate(VICoordinate::Dimension::D1, x, 0, 0, 0)
#define VI2DCoor(x, y) VI2DCoordinate(VICoordinate::Dimension::D2, x, y, 0, 0)
#define VI3DCoor(x, y, z) VI3DCoordinate(VICoordinate::Dimension::D3, x, y, z, 0)
#define VI4DCoor(x, y, z, w) VI4DCoordinate(VICoordinate::Dimension::D4, x, y, z, w)
/*
typedef QList<VICoordinate> VICoordinateList;
class VIAPI VIStraightLine :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	VI_PrivateProperty(VICoordinate, Start);
	VI_PrivateProperty(VICoordinate, End);
	_Public def_init VIStraightLine(VICoordinate start, VICoordinate end) {
		if (Start.Dim != End.Dim) {
			throw VIDimensionError("VIStraightLine::VIStraightLine() only allows coordinates of the same dimension");
		}
		Start = start; End = end;
	};
	_Public def_init VIStraightLine() {
		Start = VICoordinate(VICoordinate::Dimension::D2, 0, 0, 0, 0); End = VICoordinate(VICoordinate::Dimension::D2, 0, 0, 0, 0);
	};
	_Public bool isPointOnLine(VICoordinate& c) {
		if (Start == End) {
			return c == Start;
		}
		else {
			VICoordinate v1 = c - Start;
			VICoordinate v2 = End - Start;
			return v1.isSameVector(v2);
		}
	}
	_Public bool operator== (VIStraightLine& l) {
		if (Start == l.Start && End == l.End) {
			return true;
		}
		if (isPointOnLine(l.Start) && isPointOnLine(l.End)) {
			return true;
		}
		return false;
	}
	_Public bool operator!= (VIStraightLine& l) {
		return !(*this == l);
	}
	_Public VICoordinate getVector() {
		return End - Start;
	}
	_Public VICoordinate interpolation(double percent) {
		VICoordinate v = getVector();
		return Start + v * percent;
	}
	_Public double getLineLength() {
		return Start.getDistanceTo(End);
	}
};
class VIAPI VIBesselLine :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_PrivateProperty(VICoordinateList, BesselCoefficientPoints);
	VI_PrivateProperty(VICoordinateList, BasselRawPoints);
	_Public def_init VIBesselLine(VICoordinateList basselRawPoints) {
		BasselRawPoints = basselRawPoints;
		BesselCoefficientPoints = getBesselCoefficient(basselRawPoints);
	};
	_Public void setRawCoordinates(VICoordinateList basselRawPoints) {
		BasselRawPoints = basselRawPoints;
		BesselCoefficientPoints = getBesselCoefficient(basselRawPoints);
	};
	_Public static VICoordinateList getBesselCoefficient(VICoordinateList PointMat) {
		VICoordinate::Dimension dim = PointMat[0].Dim;
		VICoordinateList ret;
		int n = PointMat.length() - 1;
		int m = 0;
		VICoordinate vec(dim, 0, 0, 0, 0);
		for (auto i = PointMat.begin(); i != PointMat.end(); i++) {
			if (i->Dim != dim) {
				throw VIDimensionError("VIBesselLine::getBesselCoefficient() only allows coordinates of the same dimension");
			}
			vec.X = i->X * VIMath::combination(n, m);
			vec.Y = i->Y * VIMath::combination(n, m);
			vec.Z = i->Z * VIMath::combination(n, m);
			vec.W = i->W * VIMath::combination(n, m);
			ret.append(vec);
			m++;
		}
		return ret;
	}
	_Public VICoordinate interpolation(double percent) {
		return getBesselValue(BesselCoefficientPoints, percent);
	}
	_Public static VICoordinate getBesselValue(VICoordinateList BesselCoefficient, float p) {
		VICoordinate::Dimension dim = BesselCoefficient[0].Dim;
		VICoordinate ret(dim, 0, 0, 0, 0);
		int n = BesselCoefficient.length() - 1;
		int m = 0;
		for (auto i = BesselCoefficient.begin(); i != BesselCoefficient.end(); i++) {
			if (i->Dim != dim) {
				throw VIDimensionError("VIBesselLine::getBesselValue() only allows coordinates of the same dimension");
			}
			ret.X += i->X * qPow(p, m) * qPow(1.0 - p, n - m);
			ret.Y += i->Y * qPow(p, m) * qPow(1.0 - p, n - m);
			ret.Z += i->Z * qPow(p, m) * qPow(1.0 - p, n - m);
			ret.W += i->W * qPow(p, m) * qPow(1.0 - p, n - m);
			m++;
		}
		return ret;
	}
};
*/
class VIPublicAPI VIStepper :public VIObject
{
	Q_OBJECT;
	VI_PrivateProperty(long long, Begin);
	VI_PrivateProperty(long long, End);
	VI_PrivateProperty(int, Step);
	VI_PrivateProperty(long long, Current);
	_Public def_init VIStepper(long long begin, long long end, int step, VISuper* parent = VI_NULLPTR) :VIObject(parent) {
		Begin = begin; End = end; Step = step;
		Current = begin;
	};
	_Public long long next() {
		if (Current + Step > End) {
			Current = End;
			return Current;
		}
		else {
			Current += Step;
			return Current;
		}
	};
	_Public double next_p() {
		if (Current + Step > End) {
			Current = End;
			return 1.0;
		}
		else {
			Current += Step;
			return (double)(Current - Begin) / (double)(End - Begin);
		}
	}
};
