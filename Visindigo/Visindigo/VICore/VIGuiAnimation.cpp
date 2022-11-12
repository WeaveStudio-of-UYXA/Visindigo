#include "VIGuiAnimation.h"
void VIAnimationEvent::setAnimationProcess(VIAnimationEventProcess* process) {
	if (this->Process != Q_NULLPTR) {
		disconnect(this, SIGNAL(addEventLater(VIAnimationEvent*)), Process, SLOT(addEvent(VIAnimationEvent*)));
	}
	this->Process = process;
	connect(this, SIGNAL(addEventLater(VIAnimationEvent*)), Process, SLOT(addEvent(VIAnimationEvent*)));
}
void VIAnimationEvent::active() {
	if (!ALIVE) {
		this->preInit();
		emit addEventLater(this);
		//this->Process->addEvent(this);
	}
};