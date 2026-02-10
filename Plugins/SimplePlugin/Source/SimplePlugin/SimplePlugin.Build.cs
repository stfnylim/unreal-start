// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

/// <summary>
/// Build configuration file for the SimplePlugin module.
/// Defines module dependencies and compilation settings.
/// </summary>
public class SimplePlugin : ModuleRules
{
	public SimplePlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		// Use precompiled headers for faster compilation
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		// Public dependencies - modules that are exposed in our public headers
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// Add other public dependencies here
			}
		);

		// Private dependencies - modules used only in our implementation files
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",           // Required for UI elements
				"SlateCore",       // Required for UI styling
				"UnrealEd",        // Required for editor integration
				"ToolMenus",       // Required for extending editor menus
			}
		);
	}
}
