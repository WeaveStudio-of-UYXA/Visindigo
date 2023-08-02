import sys
import os

InstallPackName = "InstallPackCache"
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
    print("backups template done")
    
def recoverTemplate(path):
    # copy VisindigoTemplateProjectBackup to VisindigoTemplateProject
    print("recover template")
    if os.path.exists(path+"/VisindigoTemplateProject"):
        os.system("rd /s /q "+path.replace("/","\\")+"\\VisindigoTemplateProject")
    os.system("xcopy "+path.replace("/","\\")+"\\VisindigoTemplateProjectBackup "+path.replace("/","\\")+"\\VisindigoTemplateProject /e /i /h")
    print("recover template done")

def changeVersionInTemplate(path):
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
            if "适用于Visindigo" in line and "和" in line:
                index1 = line.find("适用于Visindigo")
                index2 = line.find("和")
                line = line[:index1]+"适用于Visindigo"+versionFullString+line[index2:]
                fileLines[i] = line
                break
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
        templateFile = open(path+"/VisindigoTemplateProject/CompileMacro.h", "r", encoding="utf-8")
        fileLines = templateFile.readlines()
        templateFile.close()
        ifdefindex = 0
        for i in range(len(fileLines)):
            if "#if VI_VERSION_MAJOR" in fileLines[i]:
                fileLines[i] = "#if VI_VERSION_MAJOR != "+str(versionMajor)+" || VI_VERSION_MINOR == "+str(versionMinor)+" || VI_VERSION_PATCH == "+str(versionPatch)+"\n"
                ifdefindex = i
                break
        fileLines[ifdefindex+1] = " #error \"This template is only for Visindigo "+versionFullString+", please use the correct version of Visindigo!\"\n"
        print("CompileMacro has been updated")
        templateFile = open(path+"/VisindigoTemplateProject/CompileMacro.h", "w", encoding="utf-8")
        templateFile.write("".join(fileLines))
        templateFile.close()
    except:
        print("Can not change version in VisindigoTemplateProject")
        return False
    return True

def zipTemplate(path):
    #use "bandzip.exe" to zip VisindigoTemplateProject to VisindigoTemplateProject.zip, command name is bz
    print("zip template")
    os.system("bz a "+(path+"/"+VersionFolderName).replace("/","\\")+"\\VisindigoTemplateProject.zip "+path.replace("/","\\")+"\\VisindigoTemplateProject\\*.*")
    print("zip template done")

def copyFileinDllDebug(path):
    #copy all the files in x64/DllDebug into VersionFolderName/x64/Debug
    print("copy debug files")
    if not os.path.exists(path+"/"+VersionFolderName+"/x64/Debug"):
        os.makedirs(path+"/"+VersionFolderName+"/x64/Debug")
    os.system("xcopy "+path.replace("/","\\")+"\\x64\\DllDebug "+(path+"/"+VersionFolderName+"/x64/Debug").replace("/","\\")+" /e /i /h")
    print("copy debug files done")

def copyFileinDllRelease(path):
    #copy all the files in x64/DllRelease into VersionFolderName/x64/Release
    print("copy release files")
    if not os.path.exists(path+"/"+VersionFolderName+"/x64/Release"):
        os.makedirs(path+"/"+VersionFolderName+"/x64/Release")
    os.system("xcopy "+path.replace("/","\\")+"\\x64\\DllRelease "+(path+"/"+VersionFolderName+"/x64/Release").replace("/","\\")+" /e /i /h")
    print("copy release files done")

def zipFullFolder(path):
    global versionFullString, InstallPackName
    #use "bandzip.exe" to zip the full folder to the zip file with the same name
    print("zip full folder")
    if not os.path.exists(path+"/InstallPack"):
        os.makedirs(path+"/InstallPack")
    #delete the old zip file if exists
    if os.path.exists(path+"/InstallPack/Visindigo_"+versionFullString+"_Windows_x64.zip"):
        os.remove(path+"/InstallPack/Visindigo_"+versionFullString+"_Windows_x64.zip")
    os.system("bz a "+path+"/InstallPack/Visindigo_"+versionFullString+"_Windows_x64.zip "+(path+"/"+InstallPackName).replace("/","\\"))
    print("zip full folder done")

def deployNow(path):
    # copy all the files in version folder to the deploy version folder
    if not os.path.exists("D:/Visindigo"):
        os.makedirs("D:/Visindigo")
    os.system("xcopy "+path.replace("/","\\")+"\\"+InstallPackName+"\\*.* D:\\Visindigo /e /i /h")

def windowsInstallPack(path):
    # spawn a new folder
    if os.path.exists(path+"/"+InstallPackName):
        os.system("rd /s /q "+path.replace("/","\\")+"\\"+InstallPackName)
    os.makedirs(path+"/"+InstallPackName)
    backupsTemplate(path)
    if not changeVersionInTemplate(path):
        recoverTemplate(path)
        print("InstallPack failed, as Template version can not be changed, all changes have been recovered")
        return
    zipTemplate(path)    
    copyFileinDllDebug(path)
    copyFileinDllRelease(path)
    zipFullFolder(path)
    deployNow(path)

if __name__ == "__main__":
    path:str = sys.path[0]
    print(path)
    os.chdir(path+"/../../")
    path = os.getcwd()
    windowsInstallPack(path)