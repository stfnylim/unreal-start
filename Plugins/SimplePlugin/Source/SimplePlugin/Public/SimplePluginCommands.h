// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Styling/AppStyle.h"

/**
 * FSimplePluginCommands
 *
 * Defines the commands/actions that can be executed from the editor UI.
 * Uses Unreal's command system to create menu items and toolbar buttons.
 *
 * This class registers the "Print Hello" command that appears in the Tools menu.
 */
class FSimplePluginCommands : public TCommands<FSimplePluginCommands>
{
public:
	FSimplePluginCommands()
		: TCommands<FSimplePluginCommands>(
			TEXT("SimplePlugin"),                           // Context name
			NSLOCTEXT("Contexts", "SimplePlugin", "Simple Plugin"), // Localized context name
			NAME_None,                                      // Parent context
			FAppStyle::GetAppStyleSetName())                // Style set name (using default app style)
	{
	}

	/**
	 * Registers all commands defined in this class.
	 * Called during plugin initialization.
	 */
	virtual void RegisterCommands() override;

public:
	/**
	 * Command to print a hello message to the output log.
	 * This will be bound to a menu item in the Tools menu.
	 */
	TSharedPtr<FUICommandInfo> PrintHelloCommand;
};
