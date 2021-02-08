// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Wicked_HavensEditorTarget : TargetRules
{
	public Wicked_HavensEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] {
													"Wicked_Havens",
													"WH_Camera",
													"WH_SaveGame",
													"WH_Dialogues",
													"WH_Menus",
													"WH_AI"
        } );
	}
}
