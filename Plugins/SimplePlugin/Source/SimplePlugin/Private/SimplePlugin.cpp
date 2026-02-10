// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimplePlugin.h"
#include "SimplePluginCommands.h"
#include "ToolMenus.h"

// Logging category for this plugin
DEFINE_LOG_CATEGORY_STATIC(LogSimplePlugin, Log, All);

#define LOCTEXT_NAMESPACE "FSimplePluginModule"

void FSimplePluginModule::StartupModule()
{
	UE_LOG(LogSimplePlugin, Log, TEXT("SimplePlugin initialized!"));

	// Register commands with the UI command system
	FSimplePluginCommands::Register();

	// Create a command list and map our command to an action
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FSimplePluginCommands::Get().PrintHelloCommand,
		FExecuteAction::CreateLambda([]()
		{
			UE_LOG(LogSimplePlugin, Log, TEXT("Hello from SimplePlugin!"));
		}),
		FCanExecuteAction());

	// Register menu extensions via startup callback
	// (ToolMenus may not be ready yet during module startup)
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSimplePluginModule::RegisterMenus));
}

void FSimplePluginModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	FSimplePluginCommands::Unregister();

	UE_LOG(LogSimplePlugin, Log, TEXT("SimplePlugin shut down."));
}

void FSimplePluginModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	// Extend the Tools menu in the level editor
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");

	// Add a section and menu entry bound to our command list
	FToolMenuSection& Section = Menu->FindOrAddSection("SimplePlugin");
	Section.AddMenuEntryWithCommandList(
		FSimplePluginCommands::Get().PrintHelloCommand,
		PluginCommands);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSimplePluginModule, SimplePlugin)
