#include "VIESEngine.h"

def_init VIESEngine::VIESEngine(QObject* parent) : VIBasicBehavior(parent) {
	Engine = new QJSEngine(this);
	
}
