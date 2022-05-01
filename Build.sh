#! /usr/bin/bash

export DOTNET_SYSTEM_GLOBALIZATION_INVARIANT=1
UEBatchFilePath="../UnrealEngine/Engine/Build/BatchFiles"

ProjectFilePath=$(find $(pwd) -iname "*.uproject")
ProjectFile=$(basename $ProjectFilePath)
Project=$(basename $ProjectFile .uproject)

echo "Building project $Project"


# Build the sources
clean="$UEBatchFilePath/Linux/Clean.sh ${Project}Editor Linux DebugGame $ProjectFilePath  -waitmutex"
build="$UEBatchFilePath/Linux/Build.sh ${Project}Editor Linux DebugGame $ProjectFilePath  -waitmutex"


# eval $clean
eval $build

#"../../UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh" Build -project=$(find $(pwd) -iname "*.uproject") -clientconfig=Development -serverconfig=Development -compile
#RunUAT BuildCookRun -project="full_project_path_and_project_name".uproject -noP4 -platform=Win64 -clientconfig=Development -serverconfig=Development -cook -maps=AllMaps -compile -stage -pak -archive -archivedirectory="Output Directory"
