/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

using UnrealBuildTool;

public class Wicked_Havens : ModuleRules
{
	public Wicked_Havens(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// the usual culprits
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		// multiplayer
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "Networking" });

		// AI
        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });

		// Wicked Havens includes
		//PrivateDependencyModuleNames.AddRange(new string[] { "WH_AI" });
	}
}
