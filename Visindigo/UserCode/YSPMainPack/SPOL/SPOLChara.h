#pragma once
#include "../../../Visindigo/VICore/VICore.h"

class SPOLCharaState :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QString StateName;
	_Public QString StateDisplayName;
	_Public QImage CharaImage;
	_Public def_init SPOLCharaState(VISuper* parent = VI_NULLPTR) :VIObject(parent) {

	}
};
class SPOLChara : public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_PrivateProperty(QString, CharaName);
	VI_PrivateProperty(QString, CharaDisplayName);
	_Public QMap<QString, SPOLCharaState*> CharaStateMap;
	_Private QString CurrentStateName;
	_Private SPOLCharaState* CurrentState = VI_NULLPTR;
	_Public def_init SPOLChara(VISuper* parent = VI_NULLPTR) :VIObject(parent) {

	}
	_Public void setState(QString stateName, QString stateDisplayName, QImage charaImage) {
		SPOLCharaState* state;
		if (CharaStateMap.contains(stateName)) { state = CharaStateMap.value(stateName); }
		else { state = new SPOLCharaState(this); }
		state->StateName = stateName;
		state->StateDisplayName = stateDisplayName;
		state->CharaImage = charaImage;
		if (!CharaStateMap.contains(stateName)) { CharaStateMap[stateName] = state; }
		if (CharaStateMap.size() == 1) { changeState(stateName); }
	}
	_Public void changeState(QString stateName) {
		if (CharaStateMap.contains(stateName)) {
			CurrentStateName = stateName;
			CurrentState = CharaStateMap.value(stateName);
		}
	}
	_Public QString getStateName() {
		return CurrentState->StateName;
	}
	_Public QString getStateDisplayName() {
		return CurrentState->StateDisplayName;
	}
	_Public QImage getStateImage() {
		return CurrentState->CharaImage;
	}
};