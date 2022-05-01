/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_Character : ModuleRules
{
	public WH_Character(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		// Unreal Engine
		PublicDependencyModuleNames.AddRange(new string[]{"Core"});
		PrivateDependencyModuleNames.AddRange(new string[] {"CoreUObject", "Engine"});
		// WH depedancy
		PrivateDependencyModuleNames.AddRange(new string[] {"WH_Core"});
	}
}
