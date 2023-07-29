#include "../VIAbstractBehavior.h"

/*
VIAbstractBehavior
*/
void VIAbstractBehavior::subside() {
	if (BehaviorState == Visindigo::Active) {
		BehaviorState = Visindigo::Subside;
	}
}

QEvent::Type VIBehaviorLoopEvent::BehaviorLoopEvent = (QEvent::Type)QEvent::registerEventType(QEvent::User + 1);