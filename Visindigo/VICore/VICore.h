#pragma once
#include "VIAbstractBehavior.h"
#include "VIBasicType.h"
#include "VIBehavior.h"
#include "VIColorTools.h"
#include "VICommand.h"
#include "VIConsole.h"
#include "VICoreFramework.h"
#include "VIDuration.h"
#include "VIECMAScripts.h"
#include "VIException.h"
#include "VIMath.h"
#include "VIMultiPlatform.h"
#include "VIObject.h"
#include "VIPackage.h"
#include "VIPathInfo.h"
#include "VITranslationHost.h"
#include "VIVersion.h"
#include "VIDocument/VIJSON.h"
#include "VIDocument/VITR.h"


#define visindigo int
#define CoreProgram main(int argc, char* argv[]){try
#define CoreProgramEnd catch(std::exception& e){VIConsole::printLine(VIConsole::inErrorStyle(e.what()));}catch(VIException& e){e.print();}return VICoreFramework::getCoreInstance()->getReturnCode();}
#define sysArgv argc, argv