/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_AttributesEditor : ModuleRules
{
	public WH_AttributesEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"SlateCore",
				"Slate",
				"UnrealEd",
				"Engine",
				"EditorWidgets",
				"ToolWidgets",
				"WH_Attributes"
			}
			);

	

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"EditorStyle",
				"EditorFramework",
				"PropertyEditor",
				"BlueprintGraph",
				"GraphEditor",
				"InputCore",

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
