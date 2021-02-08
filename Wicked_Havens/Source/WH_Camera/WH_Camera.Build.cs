// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class WH_Camera : ModuleRules
{
	public WH_Camera(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {"UMG" });
	}
}
