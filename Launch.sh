#! /usr/bin/bash

UEPath="../UnrealEngine/Engine/"
UEEdPath="$UEPath/Binaries/Linux/UnrealEditor"

ProjectFilePath=$(find $(pwd) -iname "*.uproject")
ProjectFile=$(basename $ProjectFilePath)
Project=$(basename $ProjectFile .uproject)

echo "Running project $Project"


# Build the sources
run="$UEEdPath $ProjectFilePath"

eval $run

#"../../UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh" Build -project=$(find $(pwd) -iname "*.uproject") -clientconfig=Development -serverconfig=Development -compile
#RunUAT BuildCookRun -project="full_project_path_and_project_name".uproject -noP4 -platform=Win64 -clientconfig=Development -serverconfig=Development -cook -maps=AllMaps -compile -stage -pak -archive -archivedirectory="Output Directory"
