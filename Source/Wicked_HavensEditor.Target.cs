/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

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
			"WH_Core",
			"WH_Attributes",
			"WH_Items",
			"WH_Character",
			"WH_Camera",
			"WH_AI"
			 } );
	}
}
