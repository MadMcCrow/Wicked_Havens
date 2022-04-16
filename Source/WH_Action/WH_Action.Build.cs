/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_Action : ModuleRules
{
	public WH_Action(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		// Unreal Dependency
		PublicDependencyModuleNames.AddRange(new string[]{"Core", "EnhancedInput",});
		PrivateDependencyModuleNames.AddRange(new string[] {"CoreUObject", "Engine", "DeveloperSettings"});
		// Wicked Haven Dependency
		PrivateDependencyModuleNames.AddRange(new string[] {"WH_Core"});
	}
}
