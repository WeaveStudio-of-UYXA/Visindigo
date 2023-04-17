# 前言和授权

在**Yayin Story Player**开发到0.9版本后，TsingYayin认识到YSP程序的核心UI组件QtWordGame和核心解释器组件AASPCMD并不能满足YSP程序日益增长的需求。于是TsingYayin决定先抛开YSP，开发一个基于Qt的简单二维场景框架，即本项目Visindigo。在Visindigo基本框架基本搭起来后，YSP会基于Visindigo继续开发，并且作为Visindigo开发的范例程序包含在本项目的UserCode/YSPMainPack中。

**QtWordGame**是TsingYayin基于初代YSP需求独立开发的专用于极简横版对话的UI框架。

**AASPCMD**是Ayano Aishi提出构想，由TsingYayin独立开发的SPOL脚本解释器。

**SPOL** 即`Story Player Official Language`，专用于YSP的顺序结构剧情场景描述脚本，因为可扩展性太差现已弃用，仅作为新版YSP的SPDF on ES5（`Scene Performance Description Framework`）的一部分提供。

**Visindigo**是Tsing Yayin主要开发的场景框架。TsingYayin代码水平欠佳，因此Visindigo的定位是简单、可扩展的平面呈现和交互框架，基本提供任何专业功能。但Visindigo会一直保证高度的可移植和可扩展性，确保确有需求的用户能够以自己的方式扩展Visindigo。

此项目完全开源且使用GPLv3授权，一切基于本程序的二次开发（包括扩展程序本体和编写VIJS程序）必须亦完全开源并使用GPLv3授权。本项目使用的授权许可证随时有可能变更，请用户自行关注当前许可证情况。

此项目中有部分来自于StudioIndigo（紫靛工作室）的原创图像素材，版权所有，禁止挪用。

# 参考文档

[单击跳转到参考文档](https://www.yuque.com/tsingyayin/visindigo)

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

# 致谢

Visindigo是框架型应用程序，为了向用户讲解如何使用这样的框架，我们决定重构现在在明日方舟二创社区同人剧情中经常使用的软件YSP，感谢《明日方舟》的好故事为所有在看此文的各位带来了创作的热情与欲望。

Visindigo认为Qt是当今C++中最出色的库，Visindigo大量特性，尤其是Visindigo.JS和SPDF主机依赖于Qt实现，如果没有Qt，Visindigo还有很多很多弯路要走。

Visindigo感谢万维工作室（Weave Studio）的各位同学协助了软件的开发，青雅音本人水平不高，如果没有这些同学的帮助与引导，无法进行Visindigo的开发。

Visindigo感谢紫靛工作室（Studio Indigo）的各位同学的协助与鞭策，如果没有这些同学细致广泛的运用YSP，发现其中的问题，就不会有Visindigo框架的提出与实现。由于我们最初希望的仍然是限于视觉小说框架而非通用二维场景框架之类的东西，所以我们最初的名字是Yayin Visual Story，考虑紫靛工作室名称中的Indigo可以作为靛青解释，与TsingYayin的姓氏一致，故而使框架最后得名为Visindigo，译为“流清”（或者`清流`？）

# 源代码贡献
如果您希望增加或修改Visindigo程序中的功能，请Fork本仓库，在修改完毕后提交Pull请求。

请注意：
* Visindigo主要C++内容只接受含有Qt、STL的源代码，请勿引入任何其他库，例如OpenCV、Windows API，boost等，如果必须引入，请将该库中未能跨平台的部分重新用Qt实现。（例如您如果希望引入Spine之类的东西，您应该取得Spine的全部C++源代码，并将部分内容改为Qt实现）
* Visindigo Installer主要C++内容允许引入其他第三方库。
* VIJS API指的是由Visindigo程序提供的JavaScript API，JSVI API指的是在Visindigo.JS框架下直接由JavaScript编写实现的API，您可以自由扩展JSVI API，只要您写的这些扩展能够在Visindigo.JS框架上面运行。
* 不要使用“从Qt4继承，仍然提供支持但不再继续开发”的旧版Qt组件如Qt Script。
* 不要使用C++17及之后版本中的新内容，不要使用MSVC支持不了的特性。

# 源码编译
**请注意，如果您需要获得发行版本的源码，您应该去StudioIndigo的另外一个仓库，叫做[VisindigoRelease](https://github.com/StudioIndigo-of-CYXIO/VisindigoRelease)，本仓库内的源码是代表最新开发内容的源码，可能含有不稳定因素。**
## 编译Windows版本（Windows_x86_64）
  * 安装Visual Studio 2022，勾选有关C++的内容和有关桌面开发的内容
    * 不需要勾选和移动设备开发有关的内容
  * 安装Qt5.15，该项目目前用的是Qt5.15.2，由于项目中**含有**新版Qt的特性，因此请不要使用旧版Qt。
    * 安装Qt时，应当安装MSVC2019_x64、android等平台的组件
  * 在Visual Studio 2022的扩展中搜索并安装Qt VS Tools，将Qt5.15配置到Visual Studio。
  * 在Visual Studio 2022中克隆此远程仓库，直接运行项目即可
    * 请注意您到底是在运行Visindigo还是VisindigoInstaller，右键项目可以切换启动项
  
## 编译Android版本（arm_v7）
  * 首先完成以上Windows版本操作
  * 启动Visual Studio并打开本项目，在项目资源管理器中右键“Visindigo”打开右键菜单，在Qt扩展中选择导出pri文件到任意位置
  * 将`AndroidConfig`内全部文件直接复制到含有Visual Studio项目文件（vcxproj）的目录
  * 从Qt Creator选择复制进来的pro文件以打开项目
  * 将pri文件内的SOURCE和HEAD信息覆盖pro文件内的SOURCE和HEAD信息
  * 将您的安卓设备接入计算机，并启用ADB
  * 打开`Global.h`，将
    ```C++
    #define DEPLOY WINDOWS_DEPLOY
    ```
    更改为
    ```C++
    #define DEPLOY ANDROID_DEPLOY
    ```
  * 直接运行项目
  * 不要用此方法尝试编译Android或任何其他平台（包括Windows_arm）的Visindigo Installer，因为服务器只提供Windows_x86版本的文件，Installer只检查Windows_x86的文件，即使程序能在目标平台上运行，也无法接收对应平台的文件。

# 部署Visindigo
您在默认情况下直接运行此项目，得到的程序是在main函数中加载的VIPackage对应的程序（大部分时间他会是YSP，其他时间会是某些测试程序），毕竟您不可能编译一个空框架出来跑。在这种默认情况下，参与最终可执行程序的代码只有被加载的各VIPackage所调用的Visindigo模块，其他模块不会参与到最终可执行程序。
如果您需要将全部Visindigo模块编译到一个程序中以自行创建适用于Visindigo.JS开发的环境，请在Global.h中定义：
```C++
  #define DEPLOY_AS_VIJS
```
* 注意，如果您通过C++直接使用Visindigo框架进行开发，请勿增加这一宏，这会使您的程序拥有自由的JavaScript开发接口，从而造成您的程序可以被轻易改写（相当于提供了一个Mod接口）
* 并且，如果您已经手动在您的C++程序中引入了`VIJSEngine`模块并自行建立了一个JS引擎实例，并且编写了部分开放给此实例的C++函数，使用上述宏则会使您的程序额外含有一个JS引擎实例，从而造成很大的麻烦（比如JS文件读取冲突，调试时无法确定C++函数开放给哪个实例等）。
## Windows_x86_64
* 在完成编译工作后，使用qt的MSVC 2019工具对生成文件运行`windeployqt`命令，如果仍未能运行程序，可以从Qt安装目录的`bin`文件夹下找到相关文件
  
## Android
* 项目编译完后即在您的安装设备自动部署。但您可能需要手动在设置中开启各项程序权限。  

# 运行Visindigo项目开发工具（仅限Windows）
* 确保您的计算机上拥有`Python3.8`（或与之兼容的更高版本）
* 确保您的Python有PySide2库，如果没有，您应该使用Pypi进行安装，在您的控制台执行以下命令：
  ```
  pip install pyside2
  ```
* 使用Visual Studio Code打开此项目文件夹，确保您的Visual Studio Code可以正常访问您的Python环境
* 直接运行项目即可
