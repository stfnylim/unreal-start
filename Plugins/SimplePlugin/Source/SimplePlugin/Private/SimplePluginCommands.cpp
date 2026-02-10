// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimplePluginCommands.h"

// Define localization namespace for this file
#define LOCTEXT_NAMESPACE "FSimplePluginModule"

/**
 * RegisterCommands()
 *
 * Registers all UI commands defined in this class.
 * Each command is given a localized name, description, and optional keyboard shortcut.
 */
void FSimplePluginCommands::RegisterCommands()
{
	// Register the PrintHello command
	// This creates a command that can be bound to menu items, toolbar buttons, or keyboard shortcuts
	UI_COMMAND(
		PrintHelloCommand,                                      // Command variable to initialize
		"Print Hello",                                          // Display name in menus
		"Prints 'Hello from SimplePlugin!' to the output log", // Tooltip/description
		EUserInterfaceActionType::Button,                       // Type of UI element (button, toggle, etc.)
		FInputChord());                                         // Keyboard shortcut (empty = no shortcut)
}

#undef LOCTEXT_NAMESPACE
