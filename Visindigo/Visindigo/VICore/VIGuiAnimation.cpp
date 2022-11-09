#include "VIGuiAnimation.h"
void VIAnimationEvent::active() {
	if (!ALIVE) {
		this->preInit();
		this->Process->addEvent(this);
	}
};

void VIAnimationEvent::connectProcess() {
	connect(this, SIGNAL(destroyLater(VIAnimationEvent*)), Process, SLOT(removeEvent(VIAnimationEvent*)));
}

void VIAnimationEvent::disconnectProcess() {
	disconnect(this, SIGNAL(destroyLater(VIAnimationEvent*)), Process, SLOT(removeEvent(VIAnimationEvent*)));
}
