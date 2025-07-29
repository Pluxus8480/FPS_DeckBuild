// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Game_Client : ModuleRules
{
	public Game_Client(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(new string[] { "Game_Client" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NavigationSystem","AIModule" , "Niagara"});
	}
}
