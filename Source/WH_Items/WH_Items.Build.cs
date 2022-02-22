/* Copyright © Noé Perard-Gayot 2021. */

using UnrealBuildTool;

public class WH_Items : ModuleRules
{
	public WH_Items(ReadOnlyTargetRules Target) : base(Target)
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
				"Engine",
				"DataRegistry"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Networking",
				"GameplayTags",
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
