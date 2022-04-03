/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_Character : ModuleRules
{
	public WH_Character(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		PublicDependencyModuleNames.AddRange(new string[]{"Core", "EnhancedInput",});
		PrivateDependencyModuleNames.AddRange(new string[] {"CoreUObject", "Engine", "UMG", "Networking"});
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
