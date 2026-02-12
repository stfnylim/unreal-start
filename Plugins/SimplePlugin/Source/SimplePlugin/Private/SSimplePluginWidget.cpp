// This file implements our widget — the actual UI layout and button behavior.

#include "SSimplePluginWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"

// Logging category — same one used in SimplePlugin.cpp
// "extern" is not needed here; we define a local one for this file.
DEFINE_LOG_CATEGORY_STATIC(LogSimplePluginWidget, Log, All);

// ============================================================================
// C++ CONCEPT: Function definitions
// ============================================================================
// This is the "definition" (implementation) of Construct, which was
// "declared" in the header. The syntax is:
//     ReturnType ClassName::FunctionName(parameters)
//
// The "::" is the "scope resolution operator" — it says "this function
// belongs to the SSimplePluginWidget class."
// ============================================================================

void SSimplePluginWidget::Construct(const FArguments& InArgs)
{
	// ========================================================================
	// C++ CONCEPT: Method chaining & Slate's declarative syntax
	// ========================================================================
	// Slate builds UI through nested SNew() calls. Each widget is created
	// with SNew(WidgetType) and configured with .Property(value) calls.
	//
	// The + operator adds "slots" (children) to layout widgets.
	// The [] operator sets the content of a slot.
	//
	// Think of it like HTML:
	//   SVerticalBox            =  <div style="flex-direction: column">
	//     + Slot [ TextBlock ]  =    <p>Hello World!</p>
	//     + Slot [ Button ]     =    <button>Click me</button>
	//   ;                       =  </div>
	//
	// ChildSlot is the root — every SCompoundWidget has exactly one.
	// ========================================================================

	ChildSlot
	[
		// SBox adds padding around its content. Think of it like CSS margin/padding.
		SNew(SBox)
		.Padding(20.0f)  // 20 pixels of padding on all sides
		[
			// SVerticalBox stacks children vertically (top to bottom)
			SNew(SVerticalBox)

			// --- First row: Hello World text ---
			+ SVerticalBox::Slot()
			.AutoHeight()       // Only take as much vertical space as needed
			.Padding(0, 0, 0, 10)  // Bottom padding of 10px (left, top, right, bottom)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Hello World!")))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 20))  // Bold, size 20
			]

			// --- Second row: Description text ---
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 20)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("This is your first Slate window. Try the buttons below!")))
			]

			// --- Third row: Hello button ---
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 5)
			[
				SNew(SButton)
				// ============================================================
				// C++ CONCEPT: Delegates & member function binding
				// ============================================================
				// OnClicked is a "delegate" — a variable that holds a
				// reference to a function. When the button is clicked,
				// it "invokes" (calls) whatever function is bound to it.
				//
				// FOnClicked::CreateSP(this, &ClassName::Method) binds
				// a member function. "SP" means it uses a shared pointer
				// to prevent crashes if the widget gets deleted.
				//
				// "this" = the current object (this SSimplePluginWidget)
				// "&ClassName::Method" = pointer to the member function
				// ============================================================
				.OnClicked(FOnClicked::CreateSP(this, &SSimplePluginWidget::OnHelloButtonClicked))
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Say Hello")))
				]
			]

			// --- Fourth row: Count button ---
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 5)
			[
				SNew(SButton)
				.OnClicked(FOnClicked::CreateSP(this, &SSimplePluginWidget::OnCountButtonClicked))
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Click Counter")))
				]
			]

			// --- Fifth row: Counter display ---
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 10, 0, 0)
			[
				// ============================================================
				// C++ CONCEPT: SAssignNew vs SNew
				// ============================================================
				// SNew creates a widget but doesn't save a reference to it.
				// SAssignNew creates it AND stores a pointer in a variable.
				//
				// We need to save CounterText so we can update it later
				// when the count button is clicked.
				// ============================================================
				SAssignNew(CounterText, STextBlock)
				.Text(FText::FromString(TEXT("Button clicked 0 times")))
			]
		]
	];
}

// ============================================================================
// Button click handlers
// ============================================================================

FReply SSimplePluginWidget::OnHelloButtonClicked()
{
	// UE_LOG is Unreal's logging macro. It prints to the Output Log panel.
	// The three parameters are: Category, Verbosity level, Message
	UE_LOG(LogSimplePluginWidget, Log, TEXT("Hello from SimplePlugin window!"));

	// FReply::Handled() tells the UI system "I processed this click event,
	// no need to pass it to other widgets."
	return FReply::Handled();
}

FReply SSimplePluginWidget::OnCountButtonClicked()
{
	// ========================================================================
	// C++ CONCEPT: ++ operator and FString::Printf
	// ========================================================================
	// ++ increments the variable by 1. (ClickCount++ uses the old value
	// then increments; ++ClickCount increments first then uses the new value.)
	//
	// FString::Printf works like C's printf — %d is replaced with the integer.
	// FText::FromString converts the FString to FText (UE's localization-ready
	// text type that Slate widgets expect).
	// ========================================================================
	ClickCount++;

	CounterText->SetText(
		FText::FromString(FString::Printf(TEXT("Button clicked %d times"), ClickCount))
	);

	UE_LOG(LogSimplePluginWidget, Log, TEXT("Click count: %d"), ClickCount);

	return FReply::Handled();
}
