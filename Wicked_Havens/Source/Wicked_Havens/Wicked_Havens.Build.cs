// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Wicked_Havens : ModuleRules
{
	public Wicked_Havens(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		// the usual culprits
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Gameplay ability system
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks", "OnlineSubsystem", "Networking" });
	}
}
