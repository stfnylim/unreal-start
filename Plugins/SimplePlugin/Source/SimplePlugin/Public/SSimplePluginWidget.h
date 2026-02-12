// This file defines our custom Slate widget — the contents of our editor window.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

// ============================================================================
// C++ CONCEPT: Classes & Inheritance
// ============================================================================
// In C++, a "class" is a blueprint for creating objects. It bundles together
// data (variables) and behavior (functions).
//
// "Inheritance" lets us build on top of an existing class. Here we inherit
// from SCompoundWidget, which is Unreal's base class for widgets that
// contain other widgets (text, buttons, etc).
//
// The syntax is:   class MyClass : public BaseClass
// "public" means we can access everything the base class made public.
// ============================================================================

class SSimplePluginWidget : public SCompoundWidget
{
public:
	// ========================================================================
	// C++ CONCEPT: Macros
	// ========================================================================
	// Macros are text replacements done by the preprocessor BEFORE compilation.
	// SLATE_BEGIN_ARGS / SLATE_END_ARGS are UE macros that auto-generate
	// a nested struct called "FArguments". This struct holds any parameters
	// you want to pass when creating the widget.
	//
	// Right now it's empty — we don't need any arguments yet. But you could
	// add things like:
	//     SLATE_ARGUMENT(FString, Title)
	// to pass a custom title when creating the widget.
	// ========================================================================
	SLATE_BEGIN_ARGS(SSimplePluginWidget) {}
	SLATE_END_ARGS()

	// ========================================================================
	// C++ CONCEPT: Function declarations
	// ========================================================================
	// This is a "declaration" — it tells the compiler "this function exists"
	// without providing the actual code. The code (definition) lives in the
	// .cpp file. This separation lets other files know about our functions
	// without needing all the implementation details.
	//
	// "void" means the function returns nothing.
	// "const FArguments& InArgs" takes the arguments struct by reference (&)
	// — "by reference" means we're passing the original object, not a copy.
	// ========================================================================

	/** Builds the widget's UI layout. Called once when the widget is created. */
	void Construct(const FArguments& InArgs);

private:
	// ========================================================================
	// C++ CONCEPT: Return types
	// ========================================================================
	// FReply is an Unreal type that tells the UI system "I handled this event."
	// Functions that handle button clicks must return FReply.
	// ========================================================================

	/** Called when the user clicks the Hello button. */
	FReply OnHelloButtonClicked();

	/** Called when the user clicks the Count button. */
	FReply OnCountButtonClicked();

	// ========================================================================
	// C++ CONCEPT: Member variables
	// ========================================================================
	// These are variables that belong to each instance of the class.
	// Every SSimplePluginWidget object gets its own copy.
	//
	// int32 is a 32-bit integer (a whole number). UE uses int32 instead of
	// plain "int" to guarantee the same size on all platforms.
	// ========================================================================

	/** Tracks how many times the count button was clicked. */
	int32 ClickCount = 0;

	// ========================================================================
	// C++ CONCEPT: Smart pointers (TSharedPtr)
	// ========================================================================
	// In C++, when you create objects on the "heap" (with new/MakeShareable),
	// you're responsible for deleting them when you're done. Forget to delete
	// = memory leak. Delete too early = crash.
	//
	// Smart pointers solve this. TSharedPtr is UE's shared smart pointer:
	// it counts how many things reference the object, and automatically
	// deletes it when the count reaches zero.
	//
	// STextBlock is a Slate widget that displays text.
	// We store a pointer to it so we can update the text later.
	// ========================================================================

	/** Pointer to the text block so we can update its text on button click. */
	TSharedPtr<class STextBlock> CounterText;
};
