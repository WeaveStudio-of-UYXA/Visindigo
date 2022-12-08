#include "VIGeneralBehavior.h"
VIDuration::VIDuration(VIMilliSecond msec) {
	this->MSEC = msec;
}
void VIDuration::init() {
	CURRENT = 0;
	PERCENT = 0;
	PERCENT_NL = 0;
	TIMEOUTFLAG = false;
}
void VIDuration::setDuration(VIMilliSecond msec) {
	this->MSEC = msec;
}
double VIDuration::getDuration(Unit unit = Unit::MilliSecond) {
	switch (unit) {
	case Unit::NanoSecond:
		return MSEC * 1000.0;
	case Unit::MilliSecond:
		return MSEC;
	case Unit::Second:
		return MSEC / 1000.0;
	}
}
float VIDuration::getPercent(PercentType type = PercentType::Linear) {
	switch (type) {
	case PercentType::Linear:
		return PERCENT;
	case PercentType::Nonlinear:
		return PERCENT_NL;
	}
}
void VIDuration::setBesselCoeff(VIMath::VI2DMatrix matrix) {
	this->COEFF = matrix;
}
void VIDuration::addTime(unsigned int time, Unit unit = Unit::MilliSecond) {
	if (!TIMEOUTFLAG) {
		switch (unit) {
		case Unit::NanoSecond:
			this->CURRENT += time / 1000;
			break;
		case Unit::MilliSecond:
			this->CURRENT += time;
			break;
		case Unit::Second:
			this->CURRENT += time * 1000;
			break;
		}
		PERCENT = CURRENT / MSEC;
		PERCENT_NL = VIBessel::getBesselValue(COEFF, PERCENT).y;
		if (PERCENT >= 1) {
			emit timeout();
			TIMEOUTFLAG = true;
		}
	}
}