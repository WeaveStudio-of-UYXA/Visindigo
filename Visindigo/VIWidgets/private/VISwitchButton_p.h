#pragma once
#include "../../VICore/VICore.h"
#include "../VIWidgetsTransQt.h"

class VIPublicAPI VISwitchButton;
class VIPublicAPI private_VISwitchButtonDotAnimationBehavior :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VISwitchButton;
	_Public enum class CurrentAnimationType
	{
		Hover, Leave, Press, 
	};
	VI_ProtectedProperty(VILabel*, TargetDot);
	VI_ProtectedProperty(VILabel*, TargetBackground);
	VI_ProtectedProperty(VIWidget*, TargetSwitchButton);
	VI_ProtectedProperty(CurrentAnimationType, CurrentAnimation);
	VI_ProtectedFlag(ButtonIO);
	_Public def_init private_VISwitchButtonDotAnimationBehavior(VISuper* parent = VI_NULLPTR):VIAnimationBehavior(parent) {
		TargetDot = VI_NULLPTR;
		TargetBackground = VI_NULLPTR;
		TargetSwitchButton = VI_NULLPTR;
		ButtonIO = false;
	}
	_Public virtual void onActive()override {
	}
	_Public virtual void onTick() {
		int avaliableWidth = TargetSwitchButton->width() - TargetDot->width();
		float du = VICommonMapping::sin_0_1(Duration->getPercent());
		switch (CurrentAnimation) {
			case CurrentAnimationType::Hover:
				if (ButtonIO) {
					TargetDot->move(avaliableWidth * (1 - 0.2 *du), TargetDot->y());
				}
				else {
					TargetDot->move(avaliableWidth * (0.2 * du), TargetDot->y());
				}
				break;
			case CurrentAnimationType::Leave:
				if (ButtonIO) {
					TargetDot->move(avaliableWidth * (1 - 0.2 *(1.0 -du)), TargetDot->y());
				}
				else {
					TargetDot->move(avaliableWidth * 0.2 * (1.0 - du), TargetDot->y());
				}
				break;
			case CurrentAnimationType::Press:
				if (ButtonIO) {
					TargetDot->move(avaliableWidth * (0.8 - du*0.8), TargetDot->y());
				}
				else {
					TargetDot->move(avaliableWidth * (0.2+du*0.8), TargetDot->y());
				}
				break;
		}
	}
	_Public virtual void onSubside() {
		switch (CurrentAnimation) {
			case CurrentAnimationType::Press:
				ButtonIO = !ButtonIO;
				break;
		}
	}
};