/* Copyright © Noé Perard-Gayot 2021. */

using UnrealBuildTool;
using System.Collections.Generic;

public class Wicked_HavensTarget : TargetRules
{
	public Wicked_HavensTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { 
			"Wicked_Havens",
			"WH_Inventory",
			"WH_Camera",
			"WH_AI",
			 } );
	}
}
