#pragma once
#include "SPDFScripts.h"
#include "SPOLClassicTester.h"
//SPDF 0.10.0
/*
SPOL 曾经是Story Player Official Language的缩写，现在是单词“spoil”的谐音。
SPOL是上下文无关的演出场景描述语言，用于像写剧本一样描述演出场景。
SPOL可以被以SPOL注释的方式嵌入JS中，通过SPS解析器扩展到可执行的JS代码。
由于SPOL在0.10.0版本决定彻底贯彻上下文无关的原则，因此旧版中涉及逻辑控制的语法将被废弃。
SPOL没有固定的语法，因为SPOL中的每一个单行的解析都是独立且可扩展的，因此我们将SPOL中的每一行都称作一个控制器。
控制器以每一行开始的几个字符区分，由解释器决定具体调用的解析器。（有点命令行的味道）
这就是说，在SPOL中的符号没有特定的含义，完全取决于控制器的解析器实现。
对于场景描述而言，总体而言只有以下几种描述内容：
1.谁 在 说什么  / 旁白 在 说什么 / 独白 在 说什么
2.背景是什么
3.音乐是什么 / 音效是什么
4.谁 是 什么状态（包括位置、表情、动作等）
5.谁 在 做什么（包括一切动画）
他们分别对应以下控制器：
1.讲述控制器 和/或 自由文本控制器
2.背景控制器
3.音乐控制器 和/或 音效控制器
4.角色控制器
5.动画控制器
虽然SPOL决心上下文无关，但为了使某些快捷语法能够实现，我们在内部引入了一些可以保存上下文状态的机制。
*/
class SPDFHost :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public SPDFScripts* Scripts;
	_Public SPDFWorkingEnv* WorkingEnv;
	_Public SPDFAbstractTerminal* Terminal;
	_Public def_init SPDFHost(SPDFAbstractTerminal* ter, VISuper* parent = VI_NULLPTR) :VIObject(parent) {
		Terminal = ter;
		WorkingEnv = new SPDFWorkingEnv(this);
		WorkingEnv->Terminal = Terminal;
		Scripts = new SPDFScripts(WorkingEnv, this);
	}
	_Public void installParser(SPDFAbstractControllerParser* p) {
		Scripts->addParser(p);
	}
	_Public void exec(QString filePath) {
		Scripts->exec(filePath);
	}
};