#pragma once
#include "VICodeEdit.h"
#include "VIFramework.h"
#include "VILoadingWidget.h"
#include "VIMainWindow.h"
#include "VIMultiButton.h"
#include "VIPackagePanel.h"
#include "VIPSOD.h"
#include "VIStyleSheet.h"
#include "VISwitchButton.h"
#include "VIWidget.h"
#include "VIWidgetsTransQt.h"
#include "VIWindowsTheme.h"

#define Program main(int argc, char* argv[]){try
#define ProgramEnd catch(std::exception& e){VIConsole::printLine(VIConsole::inErrorStyle(e.what()));}catch(VIException& e){VIPSOD* p = new VIPSOD(e);VICoreFramework::getAppInstance()->exec();}return VIFramework::getInstance()->getReturnCode();}