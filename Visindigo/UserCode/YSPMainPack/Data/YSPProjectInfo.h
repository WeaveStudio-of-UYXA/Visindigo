#pragma once
#include "../../../Visindigo/VICore/VICore.h"

class YSPProjectInfo :public VISettings
{
	Q_OBJECT;
	VI_OBJECT;
	_Public def_init YSPProjectInfo(QString projectName, VISuper* parent = VI_NULLPTR):VISettings(parent)
	{
		setObjectName(projectName);
	}
};