/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_Debug : ModuleRules
{
	public WH_Debug(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		// Unreal Dependency
		PublicDependencyModuleNames.AddRange(new string[]{"Core"});
		PrivateDependencyModuleNames.AddRange(new string[] {"CoreUObject", "Engine", "Slate", "SlateCore"});
	}
}
