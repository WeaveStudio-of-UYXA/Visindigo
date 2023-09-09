#include "../VIAbstractBehavior.h"

/*
VIAbstractBehavior
*/
void VIAbstractBehavior::stop() {
	if (BehaviorState == Visindigo::Active) {
		BehaviorState = Visindigo::Subside;
	}
}

QEvent::Type VIBehaviorLoopEvent::BehaviorLoopEvent = (QEvent::Type)QEvent::registerEventType(QEvent::User + 1);