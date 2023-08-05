import sys
import os
import winreg
import ctypes
ctypes.windll.kernel32.SetConsoleTitleW("Visindigo简明部署程序")
InstallPath = "D:\\Visindigo"
versionStr = "0.0.1"
def main():
    try:
        global InstallPath, versionStr
        print("我们尽可能想让这个部署程序小一点，所以决定不写UI了，您直接看命令行吧")
        workingPath = os.getcwd()
        print("当前工作目录："+workingPath)
        # 检查 Visual Studio 2022是否存在
        if not os.path.exists("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ProjectTemplates"):
            print("找不到Visual Studio 2022，无法自动部署Visindigo项目模板。部署程序仍然可以正常部署Visindigo库和生成模板文件，")
            print("但无法将其直接放置到Visual Studio 2022的识别位置。推荐您先安装Visual Studio 2022再运行此部署程序。\n")
            print("如果您按下回车键，部署程序仍将继续，您可以稍后手动将生成的模板文件复制到Visual Studio 2022的识别位置下，")
            print("这个位置是：")
            print("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ProjectTemplates")
            print("您可以按回车键继续或直接关闭程序")
            print("======正在等待您的输入======")
            input()
        print("#################################")
        print("第一阶段：部署Visindigo库")
        print("#################################")
        print("请注意：Visindigo库被默认部署在D:\\Visindigo中，如果您要修改安装目录")
        print("请在此部署程序所在的文件夹中新建文本文档名为\"path.txt\"，并在其中键入或复制您希望部署到的文件夹的路径")
        while True:
            print("完成文件后请按任意键继续。如果您不创建\"path.txt\"文件，将默认部署在D:\\Visindigo中")
            print("======正在等待您的输入======")
            input()
            print()
            if os.path.exists(workingPath+"\\path.txt"):
                f = open(workingPath+"\\path.txt", "r")
                InstallPath = f.read()
                if InstallPath[-1] == "\n": InstallPath = InstallPath[:-1]
                if InstallPath[-1]=="\\": InstallPath = InstallPath[:-1]
                f.close()
            else:
                break
            print("您的安装目录为："+InstallPath)
            print("请确认您的安装目录是否正确，如果正确请输入\"y\"并按回车键，其他任意键将重新等待您刷新安装目录")
            print("如果您输入了错误的字符，将默认部署在D:\\Visindigo中")
            print("======正在等待您的输入======")
            s = input()
            print()
            if s == "y" or s == "Y":
                break
            else :
                continue
        while True:
            print("请键入您希望部署的版本的版本号，只能安装文件中Visindigo文件夹下的文件夹名称")
            print("例如：您希望部署0.0.1版本，那么您应该直接键入0.0.1")
            print("======正在等待您的输入，输入完毕请按下回车======")
            c = input()
            c = c.replace(" ", "")
            print()
            if os.path.exists(workingPath+"\\Visindigo\\"+c+"\\") and c != "":
                versionStr = c
                break
            else:
                print("您输入的版本号不存在，请重新输入")
                continue
        print("！！！在正式部署前请您知晓！！！")
        print("本程序需要用您本次设定的安装目录写入注册表保存")
        print("因此在部署完毕后请勿手动移动Visindigo库的位置。如果您需要移动，请重新运行本部署程序")
        print("======按下回车键继续======")
        input()
        print("正在部署Visindigo库...")
        if not os.path.exists(InstallPath+"\\"+versionStr):
            os.makedirs((InstallPath+"\\"+versionStr).replace("\\", "/"))
        os.system("xcopy /e /y /q /h /i \""+workingPath+"\\Visindigo\\"+versionStr+"\" \""+InstallPath+"\\"+versionStr+"\"")
        print("部署完毕！")
        print("#################################")
        print("第二阶段：部署Visindigo项目模板和保存安装位置")
        print("#################################")
        # 检查 Visual Studio 2022是否存在
        if os.path.exists("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ProjectTemplates"):
            print("正在刷新Visual Studio 2022的模板文件...")
            os.system("xcopy /e /y /q /h /i \""+InstallPath+"\\"+versionStr+"\\VisindigoTemplateProject"+versionStr+"\" \"C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ProjectTemplates/VisindigoTemplateProject"+versionStr+"\"")
            print("刷新完毕！")
        else:
            print("Visindigo项目模板已经复制到安装目录，但无法进一步自动部署到Visual Studio 2022的识别位置。")
            print("您可以稍后将生成的模板文件复制到Visual Studio 2022的识别位置下，这些文件现在已经在您的安装目录下")
        # 保存安装位置到注册表，位于HKEY_LOCAL_MACHINE\SOFTWARE\Visindigo\ versionStr，值为InstallPath+"\\"+versionStr
        print("正在保存安装位置...")
        # 默认不存在这个注册表项
        try:
            key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, "SOFTWARE\\Visindigo", 0, winreg.KEY_ALL_ACCESS)
            winreg.CloseKey(key)
        except:
            key = winreg.CreateKey(winreg.HKEY_LOCAL_MACHINE, "SOFTWARE\\Visindigo")
            winreg.CloseKey(key)

        key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, "SOFTWARE\\Visindigo", 0, winreg.KEY_ALL_ACCESS)
        winreg.SetValueEx(key, versionStr, 0, winreg.REG_SZ, InstallPath+"\\"+versionStr)
        winreg.CloseKey(key)
        print("保存完毕！")

        print("#################################")
        print("第三阶段：部署Visindigo项模板（文件模板）")
        print("#################################")
        print("正在部署Visindigo项模板（文件模板）...")
        os.system("xcopy /e /y /q /h /i \""+workingPath+"\\Visindigo\\"+versionStr+"\\VisindigoTemplateFile\" \""+InstallPath+"\\"+versionStr+"\\VisindigoTemplateFile\"")
        if os.path.exists("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ItemTemplates"):
            print("正在刷新Visual Studio 2022的模板文件...")
            os.system("xcopy /e /y /q /h /i \""+InstallPath+"\\"+versionStr+"\\VisindigoTemplateFile\" \"C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ItemTemplates/VisindigoTemplateFile\"")
            print("刷新完毕！")
        else:
            print("Visindigo项模板（文件模板）已经生成完毕，但无法自动部署到Visual Studio 2022的识别位置。")
            print("您可以稍后将生成的模板文件复制到Visual Studio 2022的识别位置下，这些文件现在已经在您的安装目录下")
        print("#################################")
        print("部署完毕！")
        print("#################################")
        print("您可以在Visual Studio 2022中新建项目或文件时选择Visindigo模板")
        print("如果您需要部署其他版本的Visindigo库，请重新运行本程序")
        print("如果您需要卸载Visindigo库，可以直接删除您的安装目录，并删除Visual Studio 2022的模板文件")
        print("按下回车键退出程序")
        input()
        exit(0)
    except Exception as e:
        print("程序发生错误，错误信息如下：")
        print(e)
        print("请将错误信息反馈给Visindigo开发组，谢谢！")
        print("按下回车键退出程序")
        input()
        exit(-1)

if __name__ == "__main__":
    main()