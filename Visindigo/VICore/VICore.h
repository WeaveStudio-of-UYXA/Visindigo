#pragma once
#include "VIAbstractBehavior.h"
#include "VIBasicType.h"
#include "VIBehavior.h"
#include "VICommand.h"
#include "VIConsole.h"
#include "VIColorTools.h"
#include "VIPathInfo.h"
#include "VIDuration.h"
#include "VIException.h"
#include "VICoreFramework.h"
#include "VIMath.h"
#include "VIMultiPlatform.h"
#include "VIObject.h"
#include "VIPackage.h"
#include "VISettings.h"
#include "VIVersion.h"

#define visindigo int
#define CoreProgram main(int argc, char* argv[]){try
#define CoreProgramEnd catch(std::exception& e){VIConsole::printLine(VIConsole::inErrorStyle(e.what()));}catch(VIException& e){e.print();}return VICoreFramework::getCoreInstance()->getReturnCode();}
#define sysArgv argc, argv