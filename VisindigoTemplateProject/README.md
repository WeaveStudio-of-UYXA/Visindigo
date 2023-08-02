# Visindigo Template Project
此项目是适用于Visual Studio 2022 的模板项目，用于快速创建一个新的Visindigo控制台\窗口\库项目。
使用方法：
1. 将此文件夹复制到Visual Studio 2022的项目模板文件夹中，一般为：C:\Users\用户名\Documents\Visual Studio 2022\Templates\ProjectTemplates
2. 重启Visual Studio 2022
3. 在新建项目中选择Visindigo Template Project，输入项目名称，点击确定即可。
# 注意事项

1. 本模板使用Qt5.15
2. 本模板使用C++17
3. 本模板使用Visindigo 0.X.X
4. 本模板假定您的Visindigo安装在`D:\Visindigo`目录下，即Visindigo Debug dll应该位于`D:\Visindigo\x64\Debug\Visindigod.dll`。安装目录影响项目查找Visindigo的include文件、dll文件和lib文件的路径，如果您的Visindigo安装在其他目录下，请修改项目属性中的`C/C++`>`常规`>`附加包含目录`、`链接器`>`常规`>`附加库目录`和`链接器`>`输入`>`附加依赖项`。
5. 本模板默认提供由项目名称生成的命名空间，此空间内已经生成了默认的Visindigo 包元（PackageMeta）和包（Package）类，您可以在此基础上进行开发。
6. 本模板默认提供了按dll开发的编译选项，所以本模板提供了一些用于标记导出的宏，它们在CompileMacro.h文件中被定义，请您参考。
7. 本模板在编译后会自动将Visindigo的dll文件复制到输出目录。
8. 本模板的dll编译选项中使用了Python脚本，要使用此选项，请确保您的电脑上安装了Python3.9，并已经将Python3.9的安装目录添加到环境变量中（如果您在安装时勾选了“添加到环境变量”选项，那么您可以忽略此步骤），除此之外，您还需要将Visindigo安装目录中的PyTools文件夹复制到解决方案文件夹中，即与.sln文件同级的文件夹中。
9. Visindigo提供的权限标识宏_Public、_Private、_Protected、_Slot、_Signal也在内部定义，防止QT在MOC时出现错误。