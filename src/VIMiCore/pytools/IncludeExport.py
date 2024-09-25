import sys
import os
ProjectName = "Visindigo"
Config = "Debug"
def copyAllHeadFiles(path):
    """Step1: copy all head files to the include folder"""
    RootFolder = path
    NewFileFolderRoot = path+"\\..\\..\\include\\"+Config+"\\"+ProjectName
    #clear old files
    if os.path.exists(NewFileFolderRoot):
        os.system("rd /s /q "+NewFileFolderRoot)
    #copy new files
    for root, dirs, files in os.walk(RootFolder):
        for file in files:
            if file.endswith(".h"):
                RawFilePath = root+"\\"+file
                NewFileFolder = path+"\\..\\..\\include\\"+Config+"\\"+ProjectName+"\\"+os.path.relpath(root, RootFolder)
                print(RawFilePath)
                if not os.path.exists(NewFileFolder):
                    os.makedirs(NewFileFolder)
                    print("mkdir "+NewFileFolder)
                os.system("copy "+RawFilePath+" "+NewFileFolder+"\\"+file)
    
def createModuleHeadFiles(path):
    """Step2: create module head files"""
    NewFileFolderRoot = path+"\\..\\..\\include\\"+Config+"\\"+ProjectName+"\\"
    HeadFile = NewFileFolderRoot+"\\"+ProjectName
    #delete old files
    if os.path.exists(HeadFile):
        os.remove(HeadFile)
    f = open(HeadFile, "w")
    f.write("#pragma once\n")
    f.write("#include \""+ProjectName+".h\"\n")
    f.close()

if __name__ == "__main__":
    path:str = sys.path[0]
    pName:str = sys.argv[1]
    Config = sys.argv[2]
    ProjectName = pName
    print("Current Project Name is: "+pName)
    print(path)
    os.chdir(path+"/../")
    path = os.getcwd()
    copyAllHeadFiles(path)
    createModuleHeadFiles(path)



