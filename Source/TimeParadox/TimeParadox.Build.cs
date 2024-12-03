// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TimeParadox : ModuleRules
{
	public TimeParadox(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
