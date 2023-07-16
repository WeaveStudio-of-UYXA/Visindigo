import sys
import os
def copyAllHeadFiles(path):
    RootFolder = path+"\\Visindigo"
    NewFileFolderDebug = path+"\\x64\\DllDebug\\include"
    NewFileFolderRelease = path+"\\x64\\DllRelease\\include"
    #clear old files
    if os.path.exists(NewFileFolderDebug):
        os.system("rd /s /q "+NewFileFolderDebug)
    if os.path.exists(NewFileFolderRelease):
        os.system("rd /s /q "+NewFileFolderRelease)
    #copy new files
    for root, dirs, files in os.walk(RootFolder):
        for file in files:
            if file.endswith(".h"):
                RawFilePath = root+"\\"+file
                NewFileFolderDebug = path+"\\x64\\DllDebug\\include\\"+os.path.relpath(root, RootFolder)
                NewFileFolderRelease = path+"\\x64\\DllRelease\\include\\"+os.path.relpath(root, RootFolder)
                print(RawFilePath)
                if not os.path.exists(NewFileFolderDebug):
                    os.makedirs(NewFileFolderDebug)
                    print("mkdir "+NewFileFolderDebug)
                if not os.path.exists(NewFileFolderRelease):
                    os.makedirs(NewFileFolderRelease)
                    print("mkdir "+NewFileFolderRelease)
                os.system("copy "+RawFilePath+" "+NewFileFolderDebug+"\\"+file)
                os.system("copy "+RawFilePath+" "+NewFileFolderRelease+"\\"+file)
    
if __name__ == "__main__":
    path:str = sys.path[0]
    print(path)
    os.chdir(path+"/../../")
    path = os.getcwd()
    copyAllHeadFiles(path)



