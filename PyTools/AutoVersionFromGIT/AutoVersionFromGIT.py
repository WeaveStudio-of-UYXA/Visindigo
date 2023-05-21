import sys
import os
#get current path
path:str = sys.path[0]
print(path)
#cd (exit 2 folder)
os.chdir(path+"/../../")
path = os.getcwd()
print(path)
#get git commits count
gitCommitsCount = os.popen("git log --oneline | find /v /c \"\"").read()
print(gitCommitsCount)
gitCommitsCount = int(gitCommitsCount)+1

#create version .h file
if os.path.exists(path+"/Visindigo/Visindigo/VICore/private/VIAutoVersion.h"):
    os.remove(path+"/Visindigo/Visindigo/VICore/private/VIAutoVersion.h")
versionFile = open(path+"/Visindigo/Visindigo/VICore/private/VIAutoVersion.h", "w")
versionFile.write("#pragma once\n")
versionFile.write("#define VI_VERSION_BUILD "+str(gitCommitsCount))
versionFile.close()


