// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimplePlugin.h"
#include "SimplePluginCommands.h"
#include "SSimplePluginWidget.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"

DEFINE_LOG_CATEGORY_STATIC(LogSimplePlugin, Log, All);

#define LOCTEXT_NAMESPACE "FSimplePluginModule"

// ============================================================================
// C++ CONCEPT: Static variables & FName
// ============================================================================
// "static" here means this variable belongs to the file, not to any object.
// It exists once in memory and is shared. We use it as a unique ID for our tab.
//
// FName is UE's lightweight string type optimized for comparisons and lookups.
// It's used for identifiers (like tab names) rather than display text.
// ============================================================================
static const FName SimplePluginTabName("SimplePluginTab");

void FSimplePluginModule::StartupModule()
{
	UE_LOG(LogSimplePlugin, Log, TEXT("SimplePlugin initialized!"));

	// Register commands
	FSimplePluginCommands::Register();

	// ========================================================================
	// Tab Spawner Registration
	// ========================================================================
	// FGlobalTabmanager manages all editor tabs. RegisterNomadTabSpawner tells
	// it: "there's a tab called SimplePluginTab, and here's how to create it."
	//
	// "Nomad" means the tab can float or dock anywhere (vs. a tab that only
	// lives in a specific panel).
	//
	// FOnSpawnTab::CreateRaw(this, &Method) creates a delegate pointing to
	// our OnSpawnPluginTab function. "Raw" means it uses a raw pointer
	// (vs. shared pointer) — safe here because the module outlives the tab.
	// ========================================================================
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		SimplePluginTabName,
		FOnSpawnTab::CreateRaw(this, &FSimplePluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("TabTitle", "Simple Plugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);  // We open it from our own menu, not Window menu

	// Create command list and map the command to open our tab
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FSimplePluginCommands::Get().PrintHelloCommand,
		// ====================================================================
		// C++ CONCEPT: Lambdas (anonymous functions)
		// ====================================================================
		// A lambda is a function you define inline — no name needed.
		// Syntax:  [captures](parameters) { body }
		//
		// [] = capture list: what outside variables the lambda can use
		//   []      = capture nothing
		//   [this]  = capture the current object (so we can call our methods)
		//   [=]     = capture everything by copy
		//   [&]     = capture everything by reference
		//
		// This lambda opens our tab when the menu item is clicked.
		// ====================================================================
		FExecuteAction::CreateLambda([]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(SimplePluginTabName);
		}),
		FCanExecuteAction());

	// Register menu extensions
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSimplePluginModule::RegisterMenus));
}

void FSimplePluginModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	// Unregister the tab so the editor doesn't try to spawn it after we're gone
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SimplePluginTabName);

	FSimplePluginCommands::Unregister();

	UE_LOG(LogSimplePlugin, Log, TEXT("SimplePlugin shut down."));
}

void FSimplePluginModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
	FToolMenuSection& Section = Menu->FindOrAddSection("SimplePlugin");
	Section.AddMenuEntryWithCommandList(
		FSimplePluginCommands::Get().PrintHelloCommand,
		PluginCommands);
}

// ============================================================================
// Tab spawner — creates the window contents
// ============================================================================
TSharedRef<SDockTab> FSimplePluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// SNew(SDockTab) creates the dockable tab container.
	// Inside it, SNew(SSimplePluginWidget) creates our custom widget.
	// This is the same pattern as before — nested Slate widgets.
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)  // Can float/dock anywhere
		[
			SNew(SSimplePluginWidget)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSimplePluginModule, SimplePlugin)
