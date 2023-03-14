#include "VIJSEngine.h"

def_init VIJSEngine::VIJSEngine(QObject* parent) : QObject(parent) {
	Engine = new QJSEngine(this);
	
}
