// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Wicked_Havens : ModuleRules
{
	public Wicked_Havens(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// the usual culprits
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		// multiplayer
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "Networking" });

		// AI
        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });

		// Wicked Havens includes
		//PrivateDependencyModuleNames.AddRange(new string[] { "WH_AI" });
	}
}
