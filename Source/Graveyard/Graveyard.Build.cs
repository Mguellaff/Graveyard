// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Graveyard : ModuleRules
{
	public Graveyard(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
