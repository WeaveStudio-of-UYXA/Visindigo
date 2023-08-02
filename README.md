# 前言和授权
**Visindigo**是基于Qt的应用程序开发拓展，在Qt的基础上提供一些适用于游戏开发的基本对象，以及适用于桌面程序开发的小组件。

**Visindigo**最开始只是YSP的重构，但在重构过程中，我们认为某些内容对于应用程序开发来说实际上具有一定的可复用性，于是我们决定将其拆分出来，作为一个独立的框架存在。有关YSP程序的开发，已经转移到了其他仓库，此处不再赘述。

# 参考文档

[单击跳转到参考文档](https://www.yuque.com/tsingyayin/visindigo)

# 使用Visindigo
1. 安装Qt，当前Qt版本为5.15.2
2. 安装Visual Studio 2022，安装C++桌面开发组件
3. 在Visual Studio 2022中安装扩展“Qt Visual Studio Tools”、“Force UTF-8"
4. 将Qt配置到Qt Visual Studio Tools中
5. 将Visindigo安装文件放置在D:\Visindigo目录下，检查Visindigo Debug dll路径应该位于`D:\Visindigo\x64\Debug\Visindigod.dll`。
6. 将Visindigo安装文件中的VisindigoTemplateProject文件夹复制到Visual Studio 2022的项目模板文件夹中，它位于`C:\Users\您的用户名\Documents\Visual Studio 2022\Templates\ProjectTemplates`。
7. 在Visual Studio中新建项目，选择Visindigo TemplateProject，输入项目名称，点击确定。
8. 如果您需要开发Visindigo dll，请您将Visindigo安装文件中的PyTools文件夹复制到您的解决方案根目录，即与您的解决方案文件（.sln）同级的目录中。并且您需要安装Python3.9，并在安装时勾选“Add Python to PATH”（将Python添加到环境变量中），若您忘记此项或不记得是否有勾选此项，您可以在网络上查找教程，即“如何将Python添加到环境变量中”。

# 问题反馈和国际化 Feedback & i18n

## 问题反馈
此项目维护时采用中文进行交流（无论是简体中文或者繁体中文），如果您的母语不是中文，您应该采用双语进行沟通。

我们希望您首先用您的母语进行表达，之后再附上对应的中文翻译。如果您不能自己将其译为中文，您可以考虑采用翻译引擎，例如Bing，Baidu，Google等。

我们的回复也会遵循类似顺序，我们会首先用您的母语进行回复，这一回复是由翻译引擎翻译自中文的，在这之后我们会附上中文原文。

This project is maintained in Chinese (either simplified Chinese or traditional Chinese). If your mother tongue is not Chinese, you should communicate in bilingual.

We hope you will first express in your native language, and then attach the corresponding Chinese translation. If you cannot translate it into Chinese yourself, you can consider using translation engines, such as Bing, Baidu, Google, etc.

Our reply will follow a similar order. We will reply in your native language first. This reply is translated from Chinese by the translation engine. After that, we will attach the original Chinese text.

## 国际化
關於此軟體內的多語言翻譯問題，我們希望有各個語種的用戶能做出貢獻，如果後續確有此需要，我們會指出需要被翻譯的內容。

With regard to multilingual translation in this software, we hope that users of all languages can contribute. If this is really necessary in the future, we will point out what needs to be translated.

このソフトウェア内の多言語翻訳の問題については、各言語のユーザーが貢献することを期待しています。もしその後、この必要があれば、翻訳される必要がある内容を指摘します。

이 소프트웨어 내의 다국어 번역 문제에 관하여, 우리는 각 언어의 사용자가 공헌할 수 있기를 희망하며, 만약 후속으로 확실히 이러한 수요가 있다면, 우리는 번역되어야 할 내용을 지적할 것이다.

# 源代码贡献
如果您希望增加或修改Visindigo程序中的功能，请Fork本仓库，在修改完毕后提交Pull请求。

请注意：
* Visindigo主要C++内容只接受含有Qt、STL的源代码，请勿引入任何其他库，例如OpenCV、Windows API，boost等，如果必须引入，请将该库中未能跨平台的部分重新用Qt实现。（例如您如果希望引入Spine之类的东西，您应该取得Spine的全部C++源代码，并将部分内容改为Qt实现）
* VIJS API指的是由Visindigo程序提供的JavaScript API，JSVI API指的是在Visindigo.JS框架下直接由JavaScript编写实现的API，您可以自由扩展JSVI API，只要您写的这些扩展能够在Visindigo.JS框架上面运行。
* 不要使用“从Qt4继承，仍然提供支持但不再继续开发”的旧版Qt组件如Qt Script。
* 不要使用C++20及之后版本中的新内容，不要使用MSVC支持不了的特性。

# 致谢

Visindigo是框架型应用程序，为了向用户讲解如何使用这样的框架，我们使用此框架了重构现在在明日方舟二创社区同人剧情中经常使用的软件YSP，感谢《明日方舟》的好故事为所有在看此文的各位带来了创作的热情与欲望。

Visindigo认为Qt是当今C++中最出色的库，Visindigo大量特性，尤其是Visindigo.JS和SPDF主机依赖于Qt实现，如果没有Qt，Visindigo还有很多很多弯路要走。

Visindigo感谢万维工作室（Weave Studio）的各位同学协助了软件的开发，青雅音本人水平不高，如果没有这些同学的帮助与引导，无法进行Visindigo的开发。

Visindigo感谢紫靛工作室（Studio Indigo）的各位同学的协助与鞭策，如果没有这些同学细致广泛的运用YSP，发现其中的问题，就不会有Visindigo框架的提出与实现。由于我们最初希望的仍然是限于视觉小说框架而非通用二维场景框架之类的东西，所以我们最初的名字是Yayin Visual Story，考虑紫靛工作室名称中的Indigo可以作为靛青解释，与TsingYayin的姓氏一致，故而使框架最后得名为Visindigo，译为“流清”（或者`清流`？）


