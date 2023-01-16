#pragma once
#include "../../VICore/VIGeneralBehavior.h"
#include "../../../CommonEdit/CECore/CEMacro.h"

class VIHitGeometry :public QObject {
	Q_OBJECT;
	_Private VIMath::VIVector3 LOCATION;
	_Private VIMath::VIVector3 RADIUS;
	_Public VIMath::VIVector3 getLocation() {
		return LOCATION;
	}
	_Public VIMath::VIVector3 getRadius() {
		return RADIUS;
	}
	_Public void setLocation(VIMath::VIVector3 location) {
		LOCATION = location;
	}
	_Public void setRadius(VIMath::VIVector3 radius) {
		RADIUS = radius;
	}
	_Public void setGeometry(VIMath::VIVector3 location, VIMath::VIVector3 radius) {
		LOCATION = location;
		RADIUS = radius;
	}
	_Public bool ifHit(VIHitGeometry* target) {
		return (abs(LOCATION.x - target->getLocation().x) < RADIUS.x + target->getRadius().x) &&
			(abs(LOCATION.y - target->getLocation().y) < RADIUS.y + target->getRadius().y) &&
			(abs(LOCATION.z - target->getLocation().z) < RADIUS.z + target->getRadius().z);
	}
	_Public bool ifHit(VIMath::VIVector3 location, VIMath::VIVector3 radius) {
		return (abs(LOCATION.x - location.x) < RADIUS.x + radius.x) &&
			(abs(LOCATION.y - location.y) < RADIUS.y + radius.y) &&
			(abs(LOCATION.z - location.z) < RADIUS.z + radius.z);
	}
	_Public VIMath::VIVector3 getRelativeLocation(VIMath::VIVector3 location) {
		return { LOCATION.x - location.x, LOCATION.y - location.y, LOCATION.z - location.z };
	}
};
class VIHitBox :public QObject {
	Q_OBJECT
};