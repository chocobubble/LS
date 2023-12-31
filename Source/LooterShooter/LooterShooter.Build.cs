// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LooterShooter : ModuleRules
{
	public LooterShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"EnhancedInput",
			"UMG",
			"NavigationSystem",
			"AIModule",
			"GameplayTasks",
			"CableComponent",
			"Niagara",
			"MultiplayerSessions",
			"OnlineSubsystem",
			"OnlineSubsystemSteam",
			"ExamplePlugin",
			"protobuf",
			"HTTP"});

		//PublicIncludePathModuleNames.AddRange(new string[] { "ExamplePlugin/Public", "ExamplePlugin/Private" });
	}
}
