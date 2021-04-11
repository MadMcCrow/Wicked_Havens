/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

using UnrealBuildTool;
using System.Collections.Generic;

public class Wicked_HavensTarget : TargetRules
{
	public Wicked_HavensTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Wicked_Havens" } );
	}
}
