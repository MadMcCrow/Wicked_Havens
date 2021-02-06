// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class WH_AI : ModuleRules
{
	public WH_AI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// the usual culprits
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });

		// Sadly we cannot do away with this
		PublicDependencyModuleNames.Add("GameplayTasks");
	}
}
