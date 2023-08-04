import sys
import os
"""
This file is only for Windows x86_64 deploy
"""
InstallPackName = "InstallPackCache\\Visindigo"
VersionFolderName = "00"
versionMajor = 0
versionMinor = 0
versionPatch = 0
versionFullString = ""
def backupsTemplate(path):
    # copy VisindigoTemplateProject to VisindigoTemplateProjectBackup
    print("backups template")
    if os.path.exists(path+"/VisindigoTemplateProjectBackup"):
        os.system("rd /s /q "+path.replace("/","\\")+"\\VisindigoTemplateProjectBackup")
    os.system("xcopy "+path.replace("/","\\")+"\\VisindigoTemplateProject "+path.replace("/","\\")+"\\VisindigoTemplateProjectBackup /e /i /h")
    if os.path.exists(path+"/VisindigoTemplateFileBackup"):
        os.system("rd /s /q "+path.replace("/","\\")+"\\VisindigoTemplateFileBackup")
    os.system("xcopy "+path.replace("/","\\")+"\\VisindigoTemplateFile "+path.replace("/","\\")+"\\VisindigoTemplateFileBackup /e /i /h")
    print("backups template done")
    
def recoverTemplate(path):
    # copy VisindigoTemplateProjectBackup to VisindigoTemplateProject
    print("recover template")
    if os.path.exists(path+"/VisindigoTemplateProject"):
        os.system("rd /s /q "+path.replace("/","\\")+"\\VisindigoTemplateProject")
    os.system("xcopy "+path.replace("/","\\")+"\\VisindigoTemplateProjectBackup "+path.replace("/","\\")+"\\VisindigoTemplateProject /e /i /h")
    if os.path.exists(path+"/VisindigoTemplateFile"):
        os.system("rd /s /q "+path.replace("/","\\")+"\\VisindigoTemplateFile")
    os.system("xcopy "+path.replace("/","\\")+"\\VisindigoTemplateFileBackup "+path.replace("/","\\")+"\\VisindigoTemplateFile /e /i /h")
    print("recover template done")

def changeVersionInTemplateProject(path):
    global versionMajor, versionMinor, versionPatch, versionFullString, InstallPackName, VersionFolderName
    # get version from Visindigo/VICore/VIVersion.h, the macro is VI_VERSION_MAJOR and VI_VERSION_MINOR
    versionFile = open(path+"/Visindigo/VICore/VIVersion.h", "r", encoding="utf-8")
    for line in versionFile.readlines():
        if "#define VI_VERSION_MAJOR" in line:
            versionMajor = int(line.split(" ")[-1])
        elif "#define VI_VERSION_MINOR" in line:
            versionMinor = int(line.split(" ")[-1])
        elif "#define VI_VERSION_PATCH" in line:
            versionPatch = int(line.split(" ")[-1])
    versionFile.close()
    if versionMajor == 0 and versionMinor == 0 and versionPatch == 0:
        print("Can not get version from Visindigo/VICore/VIVersion.h")
        return False
    try:
        versionString = str(versionMajor)+"."+str(versionMinor)
        versionFullString = versionString+"."+str(versionPatch)
        VersionFolderName = InstallPackName + "/" + versionFullString
        print("Visindigo version now is : "+versionFullString)
        #change version in VisindigoTemplateProject/VisindigoProject.vstemplate
        templateFile = open(path+"/VisindigoTemplateProject/VisindigoProject.vstemplate", "r", encoding="utf-8")
        fileLines = templateFile.readlines()
        templateFile.close()
        for i in range(len(fileLines)):
            line = fileLines[i]
            if "<Description>" in line and "</Description>" in line:
                fileLines[i] = "    <Description>适用于Visindigo"+versionFullString+"和Qt5.15开发的项目模板</Description>\n"
            elif "<Name>" in line and "</Name>" in line:
                fileLines[i] = "    <Name>Visindigo "+versionFullString+" Template Project</Name>\n"
        print("VSTemplate has been updated")
        templateFile = open(path+"/VisindigoTemplateProject/VisindigoProject.vstemplate", "w", encoding="utf-8")
        templateFile.write("".join(fileLines))
        templateFile.close()

        #change version in VisindigoTemplateProject/TEMP.vcxproj
        templateFile = open(path+"/VisindigoTemplateProject/TEMP.vcxproj", "r", encoding="utf-8")
        fileLines = templateFile.readlines()
        templateFile.close()
        for i in range(len(fileLines)):
            line = fileLines[i]
            if "D:\\Visindigo\\" in line and "\\x64\\" in line:
                index1 = line.find("D:\\Visindigo\\")
                index2 = line.find("\\x64\\")
                line = line[:index1]+"D:\\Visindigo\\"+versionFullString+line[index2:]
                fileLines[i] = line
        print("VCXProj has been updated")
        templateFile = open(path+"/VisindigoTemplateProject/TEMP.vcxproj", "w", encoding="utf-8")
        templateFile.write("".join(fileLines))
        templateFile.close()

        #change version in VisindigoTemplateProject/CompileMacro.h
        templateFile = open(path+"/VisindigoTemplateProject/TEMPCompileMacro.h", "r", encoding="utf-8")
        fileLines = templateFile.readlines()
        templateFile.close()
        ifdefindex = 0
        for i in range(len(fileLines)):
            if "#if VI_VERSION_MAJOR" in fileLines[i]:
                fileLines[i] = "#if VI_VERSION_MAJOR != "+str(versionMajor)+" || VI_VERSION_MINOR != "+str(versionMinor)+" || VI_VERSION_PATCH != "+str(versionPatch)+"\n"
                ifdefindex = i
                break
        fileLines[ifdefindex+1] = " #error \"This template is only for Visindigo "+versionFullString+", please use the correct version of Visindigo!\"\n"
        print("CompileMacro has been updated")
        templateFile = open(path+"/VisindigoTemplateProject/TEMPCompileMacro.h", "w", encoding="utf-8")
        templateFile.write("".join(fileLines))
        templateFile.close()
    except:
        print("Can not change version in VisindigoTemplateProject")
        return False
    return True

def zipTemplateProject(path):
    global versionFullString, VersionFolderName
    #use "bandzip.exe" to zip VisindigoTemplateProject to VisindigoTemplateProject.zip, command name is bz
    print("zip template")
    os.system("bz a "+(path+"/"+VersionFolderName).replace("/","\\")+"\\VisindigoTemplateProject"+versionFullString+".zip "+path.replace("/","\\")+"\\VisindigoTemplateProject\\*.*")
    print("zip template done")

def copyFileinDllDebug(path):
    global VersionFolderName
    #copy all the files in x64/DllDebug into VersionFolderName/x64/Debug
    print("copy debug files")
    if not os.path.exists(path+"/"+VersionFolderName+"/x64/Debug"):
        os.makedirs(path+"/"+VersionFolderName+"/x64/Debug")
    os.system("xcopy "+path.replace("/","\\")+"\\x64\\DllDebug "+(path+"/"+VersionFolderName+"/x64/Debug").replace("/","\\")+" /e /i /h")
    print("copy debug files done")

def copyFileinDllRelease(path):
    global VersionFolderName
    #copy all the files in x64/DllRelease into VersionFolderName/x64/Release
    print("copy release files")
    if not os.path.exists(path+"/"+VersionFolderName+"/x64/Release"):
        os.makedirs(path+"/"+VersionFolderName+"/x64/Release")
    os.system("xcopy "+path.replace("/","\\")+"\\x64\\DllRelease "+(path+"/"+VersionFolderName+"/x64/Release").replace("/","\\")+" /e /i /h")
    print("copy release files done")

def copyTemplateFile(path):
    global VersionFolderName
    #copy all the files in VisindigoTemplateFile into VersionFolderName/VisindigoTemplateFile
    print("copy template files")
    if not os.path.exists(path+"/"+VersionFolderName+"/VisindigoTemplateFile"):
        os.makedirs(path+"/"+VersionFolderName+"/VisindigoTemplateFile")
    os.system("xcopy "+path.replace("/","\\")+"\\VisindigoTemplateFile "+(path+"/"+VersionFolderName+"/VisindigoTemplateFile").replace("/","\\")+" /e /i /h")
    print("copy template files done")

def zipFullFolder(path):
    global versionFullString, InstallPackName
    #use "bandzip.exe" to zip the full folder to the zip file with the same name
    print("zip full folder")
    if not os.path.exists(path+"/InstallPack"):
        os.makedirs(path+"/InstallPack")
    #delete the old zip file if exists
    if os.path.isfile(path+"/InstallPack/Visindigo_"+versionFullString+"_Windows_x64.zip"):
        print("delete old zip file")
        os.remove(path+"/InstallPack/Visindigo_"+versionFullString+"_Windows_x64.zip")
    os.system("bz a "+path+"/InstallPack/Visindigo_"+versionFullString+"_Windows_x64.zip "+(path+"/"+InstallPackName).replace("/","\\"))
    print("zip full folder done")

def deployNow(path):
    global InstallPackName
    # copy all the files in version folder to the deploy version folder
    print("deploy now")
    if not os.path.exists("D:/Visindigo"):
        os.makedirs("D:/Visindigo")
    os.system("xcopy "+path.replace("/","\\")+"\\"+InstallPackName+" D:\\Visindigo /e /i /h /y")
    # copy template zip to VS document template folder
    print("copy template zip to VS document template folder")
    if not os.path.exists("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ProjectTemplates"):
        print("Can not find Visual Studio 2022")
    else:
        if os.path.isfile("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ProjectTemplates"+"/VisindigoTemplateProject"+versionFullString+".zip"):
            os.remove("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ProjectTemplates"+"/VisindigoTemplateProject"+versionFullString+".zip")
        os.system("copy "+(path+"/"+VersionFolderName).replace("/","\\")+"\\VisindigoTemplateProject"+versionFullString+".zip \"C:\\Users\\"+os.getlogin()+"\\Documents\\Visual Studio 2022\\Templates\\ProjectTemplates\" /y")
        #copy template files
    print("copy template files")
    if not os.path.exists("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ItemTemplates"):
        print("Can not find Visual Studio 2022")
    else:
        if os.path.exists("C:/Users/"+os.getlogin()+"/Documents/Visual Studio 2022/Templates/ItemTemplates"+"/VisindigoTemplateFile"):
            os.system("rd /s /q "+"C:\\Users\\"+os.getlogin()+"\\Documents\\Visual Studio 2022\\Templates\\ItemTemplates"+"\\VisindigoTemplateFile")
        os.system("xcopy "+(path+"/"+VersionFolderName).replace("/","\\")+"\\VisindigoTemplateFile \"C:\\Users\\"+os.getlogin()+"\\Documents\\Visual Studio 2022\\Templates\\ItemTemplates\\VisindigoTemplateFile\" /e /i /h /y")
    print("deploy done")
    
def windows_x86_64_PackMake(path):
    global InstallPackName
    # create a new folder if not exists
    if os.path.exists(path+"/"+InstallPackName):
        os.system("rd /s /q "+path.replace("/","\\")+"\\"+InstallPackName)
    os.makedirs(path+"/"+InstallPackName)
    backupsTemplate(path) # backup the template project, in case of broken
    if not changeVersionInTemplateProject(path):
        recoverTemplate(path)
        print("InstallPack failed, as Template version can not be changed, all changes have been recovered")
        return
    zipTemplateProject(path) # zip the Visual Studio Project Template
    copyFileinDllDebug(path) # copy Visindigo Debug files (include, lib, dll, pdb, ilk, exp)
    copyFileinDllRelease(path) # copy Visindigo Release files (include, lib, dll, exp)
    copyTemplateFile(path) # zip the Visual Studio Item Template
    zipFullFolder(path) # generate the full folder zip file
    deployNow(path) # copy Visindigo to the deploy folder, copy template to VS template folder

if __name__ == "__main__":
    path:str = sys.path[0]
    print(path)
    os.chdir(path+"/../../")
    path = os.getcwd()
    windows_x86_64_PackMake(path)