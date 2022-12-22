#pragma once
#include "../../../Visindigo/VIWidgets/VIGUILabel/VIGUILabelBase.h"
#include "../../../Visindigo/VICore/VIAnimation.h"
#include "../../../Visindigo/VICore/VIQtExtensionMethod.h"

namespace GUI
{
	class VIGUILabel :public VIBase::VIGUILabel, QLabel
	{
		Q_OBJECT;
	};
}