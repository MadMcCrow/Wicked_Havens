/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_Core : ModuleRules
{
	public WH_Core(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		// Unreal Dependancy
		PublicDependencyModuleNames.AddRange(new string[]{"Core"});
		PrivateDependencyModuleNames.AddRange(new string[] {"CoreUObject", "Engine"});
	}
}
