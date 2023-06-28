#include "../VIAbstractBehavior.h"

/*
VIAbstractBehavior
*/
void VIAbstractBehavior::subside() {
	if (BehaviorState == State::Active) {
		BehaviorState = State::Subside;
	}
}

QEvent::Type VIBehaviorLoopEvent::BehaviorLoopEvent = (QEvent::Type)QEvent::registerEventType(QEvent::User + 1);