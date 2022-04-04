/* Copyright © Noé Perard-Gayot 2022. */

using UnrealBuildTool;

public class WH_GameEvent : ModuleRules
{
	public WH_GameEvent(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]{	"Core"});
		PrivateDependencyModuleNames.AddRange(new string[]{	"CoreUObject","Engine","Networking"	});
		PrivateDependencyModuleNames.AddRange(new string[]{	"WH_Core"});

	}
}
