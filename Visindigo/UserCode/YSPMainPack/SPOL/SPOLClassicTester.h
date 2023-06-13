#pragma once
#include "../../../Visindigo/VICore/VICore.h"
#include "SPOLTerminal.h"
/*
SPOLClassicTester
在YSP0.4（大概？）等没有UI的版本中，我们用了命令行测试SPOL功能。
后来做了UI之后这个功能被移除（Python版没删干净，但C++版是一点不带剩的）
我们现在要把它重新加回来
*/

class SPOLClassicTester :public VIObject, SPOLAbstractTerminal
{

};