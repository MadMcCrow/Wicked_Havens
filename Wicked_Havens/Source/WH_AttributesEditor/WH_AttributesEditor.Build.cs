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
				"UnrealEd",
				"Core",
				"CoreUObject",
				"Engine",
				"WH_Attributes"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"SlateCore",
				"Slate",
				"EditorStyle",
				"PropertyEditor",
				"BlueprintGraph",
				"GraphEditor",
				"DeveloperSettings",
				"EditorWidgets",
				"Engine"
			}
			);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
