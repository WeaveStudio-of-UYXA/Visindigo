# Visindigo 前言

Visindigo这个仓库，除去操作Git错误导致重建之外，前前后后建了又删删了又建四次。Weave Studio和Studio Indigo作出的官方回复一直说Visindigo大概年底见的事情。不过现在我的评价是几乎不可能。

Visindigo的初始概念太完美了，完美到完全超出我的编程能力和学习能力，所以每次建了又删就代表着一次设计失败的Visindigo架构。

反正我现在是想开了，我不需要一开始弄那么复杂，所以我们现在再次重头开始，希望能给所有关注cYSP和Visindigo项目的人带来新的惊喜。

# Visindigo 参考文档

[单击跳转到参考文档](https://www.yuque.com/tsingyayin/visindigo)

# Visindigo 源码编译
**请注意，如果您需要获得发行版本的源码，您应该去StudioIndigo的另外一个仓库，叫做[VisindigoRelease](https://github.com/StudioIndigo-of-CYXIO/VisindigoRelease)，本仓库内的源码是代表最新开发内容的源码，可能含有不稳定因素。**
## 编译Windows版本（Windows_x86_64）
  * 安装Visual Studio 2022，勾选有关C++的内容和有关桌面开发的内容
    * 不需要勾选和移动设备开发有关的内容
  * 安装Qt5.15，该项目目前用的是Qt5.15.2，由于项目中**可能含有**新版Qt的特性，因此请不要使用旧版Qt，至少不应该使用5.11以下的版本
    * 安装Qt时，应当安装MSVC2019_x64、android等平台的组件
  * 在Visual Studio 2022的扩展中搜索并安装Qt VS Tools，将Qt5.15配置到Visual Studio。
  * 在Visual Studio 2022中克隆此远程仓库，直接运行项目即可
    * 请注意您到底是在运行Visindigo还是VisindigoInstaller，右键项目可以切换启动项
  
## 编译Android版本（arm_v7）
  * 首先完成以上Windows版本操作
  * 启动Visual Studio并打开本项目，在项目资源管理器中右键“Visindigo”打开右键菜单，在Qt扩展中选择导出pri文件到任意位置
  * 将AndroidConfig内全部文件直接复制到含有Visual Studio项目文件（vcxproj）的目录
  * 从Qt Creator选择复制进来的pro文件以打开项目
  * 将pri文件内的SOURCE和HEAD信息覆盖pro文件内的SOURCE和HEAD信息
  * 将您的安卓设备接入计算机，并启用ADB
  * 直接运行项目
  * 不要用此方法尝试编译Android或任何其他平台（包括Windows_arm）的Visindigo Installer，因为服务器只提供Windows_x86版本的文件，Installer只检查Windows_x86的文件
