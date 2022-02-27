#! /usr/bin/python
#
#   Simply adapt calls to UAT to generate the project file according for WH
#
import os
import platform
import subprocess
import shlex

project = os.path.abspath([a for a in os.listdir() if ".uproject" in a][0])
ue_path = os.path.abspath("../UnrealEngine")

if platform.system() == "Linux":
    cmd = "\"{0}/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh\" {1} -game -engine".format(str(ue_path),str(project))
if platform.system() == "Windows":
    cmd ='\"{0}\\Engine\\Binaries\\DotNET\\UnrealBuildTool\\UnrealBuildTool.exe\" -projectfiles -project=\"{1}\" -game -rocket -progress'.format(str(ue_path),str(project))


print("Setting up {}, with Engine located at {}:".format(str(project), str(ue_path)))
subprocess.call(shlex.split(cmd))

