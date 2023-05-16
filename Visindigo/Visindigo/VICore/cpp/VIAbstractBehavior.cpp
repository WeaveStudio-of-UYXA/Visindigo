#include "../VIAbstractBehavior.h"

/*
VIAbstractBehavior
*/
void VIAbstractBehavior::passive() {
	if (BehaviorState == State::Active) {
		BehaviorState = State::Passive;
	}
}