#pragma once
#include "PythonAPI/PythonAPI.h"
#include "VITrans/VIServer.h"
class Global
{
public:
	static VIServer* VServer;
	static PythonAPI* PyAPI;
};

