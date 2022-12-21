#include "VIGeneralBehavior.h"
void VIDuration::init() {
	CURRENT = 0;
	PERCENT = 0;
	PERCENT_NL = 0;
	TIMEOUTFLAG = false;
	COEFF = VIBessel::getBesselCoefficient({ {0, 0}, {1, 1} });
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
void VIDuration::addTime(unsigned long long time, Unit unit = Unit::MilliSecond) {
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
bool VIDuration::isTimeout() {
	return this->TIMEOUTFLAG;
}



void VIGeneralBehavior::setDuration(VIMilliSecond msec) {
	this->DURATION->setDuration(msec);
}
VIMilliSecond VIGeneralBehavior::getDuration() {
	return this->DURATION->getDuration();
}
float VIGeneralBehavior::getPercent(VIDuration::PercentType type) {
	return this->DURATION->getPercent(type);
}
void VIGeneralBehavior::setBesselCoeff(VIMath::VI2DMatrix matrix) {
	return this->DURATION->setBesselCoeff(matrix);
}
void VIGeneralBehavior::setHost(VIGeneralBehaviorHost* host) {
	if (this->HOST != Q_NULLPTR) {
		disconnect(this, SIGNAL(addBehaviorLater(VIGeneralBehavior*)), HOST, SLOT(addBehavior(VIGeneralBehavior*)));
	}
	this->HOST = host;
	connect(this, SIGNAL(addBehaviorLater(VIGeneralBehavior*)), HOST, SLOT(addBehavior(VIGeneralBehavior*)));
}
void VIGeneralBehavior::active() {
	if (STATE == State::Idle) {
		this->DURATION->init();
		this->onActive();
		STATE = State::Active;
		emit addBehaviorLater(this);
	}
} 
void VIGeneralBehavior::preFrame(VINanoSecond duration) {
	this->DURATION->addTime(duration, VIDuration::Unit::NanoSecond);
	if (DURATION->isTimeout()) {
		this->onDone();
		STATE = State::Done;
	}
	else {
		this->onFrame();
	}
}
VIGeneralBehavior::State VIGeneralBehavior::getBehaviorState() {
	return this->STATE;
}