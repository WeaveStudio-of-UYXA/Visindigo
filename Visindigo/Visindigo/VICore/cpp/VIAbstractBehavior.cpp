#include "../VIAbstractBehavior.h"

/*
VIAbstractBehavior
*/
void VIAbstractBehavior::passive() {
	if (BehaviorState == State::Active) {
		BehaviorState = State::Passive;
	}
}

QEvent::Type VIBehaviorLoopEvent::BehaviorLoopEvent = (QEvent::Type)QEvent::registerEventType(QEvent::User + 1);