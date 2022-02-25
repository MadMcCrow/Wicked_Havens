#! /usr/bin/python
#
#   Simply adapt calls to UAT to generate the project file according for WH
#
import os
import platform
import subprocess
import shlex

game_project_folder  = "Wicked_Havens"
unreal_engine_folder = os.path.abspath("UnrealEngine")
project_file = os.path.abspath([a for a in os.listdir(game_project_folder) if ".uproject" in a][0])

args = [ "-game", "-rocket", "-progress", "-engine", "-projectfiles" ]

if platform.system() == "Linux":
    cmd = "\"{0}/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh\" {1} {2}".format(str(unreal_engine_folder), " ".join(args), str(project_file))
if platform.system() == "Windows":
    cmd ='\"{0}\\Engine\\Binaries\\DotNET\\UnrealBuildTool\\UnrealBuildTool.exe\" {1} -project=\"{2}\"'.format(str(unreal_engine_folder), " ".join(args), str(project_file))

print(cmd)
# Call UAT from command line
subprocess.call(shlex.split(cmd))

