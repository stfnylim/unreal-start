// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * FSimplePluginModule
 *
 * Main module class for SimplePlugin. Handles plugin lifecycle and editor integration.
 */
class FSimplePluginModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Registers the Tools menu extension. Called via UToolMenus startup callback. */
	void RegisterMenus();

	// ========================================================================
	// C++ CONCEPT: TSharedRef vs TSharedPtr
	// ========================================================================
	// TSharedRef is like TSharedPtr but can NEVER be null. It must always
	// point to a valid object. Use TSharedRef when something must exist,
	// and TSharedPtr when it might be null.
	//
	// SDockTab is Unreal's dockable tab widget (like the Details panel).
	// FSpawnTabArgs contains info about how the tab was requested.
	// ========================================================================

	/** Creates and returns the tab content when the editor needs to show our window. */
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	/** Command list that maps UI commands to actions */
	TSharedPtr<FUICommandList> PluginCommands;
};
