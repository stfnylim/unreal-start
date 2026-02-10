// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * FSimplePluginModule
 *
 * Main module class for SimplePlugin. Implements IModuleInterface to handle
 * plugin startup and shutdown lifecycle events.
 */
class FSimplePluginModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Registers the Tools menu extension. Called via UToolMenus startup callback. */
	void RegisterMenus();

	/** Command list that maps UI commands to actions */
	TSharedPtr<FUICommandList> PluginCommands;
};
