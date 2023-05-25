#pragma once
#include "VIObject.h"
/*
* Notice: All the code in this file is not tested.
* Please do not use it directly.
*/
class VICoordinate
{ 
	friend class VICoordinate;
	_Private long long X;
	_Private long long Y;
	_Private long long Z;
	_Private long long W;
	_Public def_init VICoordinate(double x, double y, double z = 0, double w = 0) {
		X = x* VI_COORDINATE_RATE; Y = y* VI_COORDINATE_RATE; Z = z* VI_COORDINATE_RATE; W = w* VI_COORDINATE_RATE;
	};
	_Public def_init VICoordinate() {
		X = 0; Y = 0; Z = 0; W = 0;
	};
	_Public def_copy VICoordinate(const VICoordinate& c) {
		X = c.X; Y = c.Y; Z = c.Z; W = c.W;
	};
	_Public VICoordinate operator=(const VICoordinate& c) {
		X = c.X; Y = c.Y; Z = c.Z; W = c.W;
		return *this;
	};
	_Public double x(){
		return (double)X / VI_COORDINATE_RATE;
	}
	_Public double y() {
		return (double)Y / VI_COORDINATE_RATE;
	}
	_Public double z() {
		return (double)Z / VI_COORDINATE_RATE;
	}
	_Public double w() {
		return (double)W / VI_COORDINATE_RATE;
	}
	_Public void setX(double x) {
		X = x* VI_COORDINATE_RATE;
	}
	_Public void setY(double y) {
		Y = y* VI_COORDINATE_RATE;
	}
	_Public void setZ(double z) {
		Z = z* VI_COORDINATE_RATE;
	}
	_Public void setW(double w) {
		W = w* VI_COORDINATE_RATE;
	}
	_Public double getDistanceTo(const VICoordinate& c) {
		return qSqrt(qPow(X - c.X, 2) + qPow(Y - c.Y, 2) + qPow(Z - c.Z, 2) + qPow(W - c.W, 2));
	}
	_Public bool isSameVector(const VICoordinate& c) {
		double rate = c.X / X;
		if (c.Y / Y - rate > VI_COORDINATE_RATE) return false;
		if (c.Z / Z - rate > VI_COORDINATE_RATE) return false;
		if (c.W / W - rate > VI_COORDINATE_RATE) return false;
		return true;
	}
	_Public bool operator== (const VICoordinate& c) {
		return X == c.X && Y == c.Y && Z == c.Z && W == c.W;
	}
	_Public bool operator!= (const VICoordinate& c) {
		return X != c.X || Y != c.Y || Z != c.Z || W != c.W;
	}
	_Public VICoordinate operator+ (const VICoordinate& c) {
		VICoordinate rtn(0, 0, 0, 0);
		rtn.X = X + c.X;
		rtn.Y = Y + c.Y;
		rtn.Z = Z + c.Z;
		rtn.W = W + c.W;
		return rtn;
	}
	_Public VICoordinate operator- (const VICoordinate& c) {
		VICoordinate rtn(0, 0, 0, 0);
		rtn.X = X - c.X;
		rtn.Y = Y - c.Y;
		rtn.Z = Z - c.Z;
		rtn.W = W - c.W;
		return rtn;
	}
	_Public VICoordinate operator* (const double d) {
		VICoordinate rtn(0, 0, 0, 0);
		rtn.X = X * d;
		rtn.Y = Y * d;
		rtn.Z = Z * d;
		rtn.W = W * d;
		return rtn;
	}
	_Public VICoordinate operator/ (const double d) {
		VICoordinate rtn(0, 0, 0, 0);
		rtn.X = X / d;
		rtn.Y = Y / d;
		rtn.Z = Z / d;
		rtn.W = W / d;
		return rtn;
	}
};

class VIStraightLine {
	VI_Property(VICoordinate, Start);
	VI_Property(VICoordinate, End);
	_Public def_init VIStraightLine(VICoordinate start, VICoordinate end) {
		Start = start; End = end;
	};
	_Public def_init VIStraightLine() {
		Start = VICoordinate(0, 0, 0, 0); End = VICoordinate(0, 0, 0, 0);
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
	_Public double getDistance() {
		return Start.getDistanceTo(End);
	}
};

class VIStepper :public VIObject
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