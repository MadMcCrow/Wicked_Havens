/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_Camera : ModuleRules
{
	public WH_Camera(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"UMG",
				"EnhancedInput"
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
