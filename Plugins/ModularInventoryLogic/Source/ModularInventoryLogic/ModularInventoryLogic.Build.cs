// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ModularInventoryLogic : ModuleRules
{
	public ModularInventoryLogic(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		
		PrivateIncludePaths.AddRange(new string[] {});
		
		PublicDependencyModuleNames.AddRange(new string[]{ "Core"});
		
		PrivateDependencyModuleNames.AddRange(new string[]{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"GameplayTags"
		});
		DynamicallyLoadedModuleNames.AddRange(new string[]{ });
	}
}
