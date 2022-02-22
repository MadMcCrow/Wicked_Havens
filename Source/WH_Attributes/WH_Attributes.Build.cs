/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_Attributes : ModuleRules
{
	public WH_Attributes(ReadOnlyTargetRules Target) : base(Target)
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
				"CoreUObject",
				"NetCore",
				"Engine"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Networking",
				"DeveloperSettings"
			}
			);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
