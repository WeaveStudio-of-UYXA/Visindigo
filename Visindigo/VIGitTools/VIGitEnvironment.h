#pragma once
#include "../VICore/VICore.h"

class VIGitEnvironment :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QString GitCmdPath;
};