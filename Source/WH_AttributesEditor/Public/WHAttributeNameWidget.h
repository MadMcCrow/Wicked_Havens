/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttribute.h"
#include "Widgets/SBoxPanel.h"

/**
 *	@class SWHAttributeNameWidget
 *	An editor widget to display an attribute name for editing by the user
 *	@see @struct FWHAttributeName
 */
class SWHAttributeNameWidget : public SVerticalBox
{
public:
	DECLARE_DELEGATE_OneParam(FOnAttributeNameChanged, TSharedPtr<FWHAttributeName>);

	SLATE_BEGIN_ARGS(SWHAttributeNameWidget)
		: _AttributeName(FWHAttributeName())
		{
			_Visibility = EVisibility::SelfHitTestInvisible;
		}
		SLATE_ATTRIBUTE(FWHAttributeName, AttributeName)
		SLATE_EVENT(FOnAttributeNameChanged, OnAttributeNameChanged)
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

private:

	// Calls the settings to obtain a list of all the Attributes currently available
	void UpdateAttributeOptions();

	// Internal Edited Attribute ;
	TAttribute<FWHAttributeName> EditedAttributeName;

	// Stores the Attribute options
	TArray<FString> AttributeNameOptionStrings;
	// Store pointers to the strings just before.
	TArray<TSharedPtr<FString>> AttributeNameOptions;

	// Called when user selects an entry
	void OnTextSelectionChanged(TSharedPtr<FString> String, ESelectInfo::Type Arg) const;

	// Called when we need to generate entries
	TSharedRef<SWidget> MakeComboEntryWidget(TSharedPtr<FString> InString) const;

	// return EditedAttributeName's GUID (as text for widget callback)
	FText GetGUIDisplayString() const;

	// return EditedAttributeName's DisplayName (as string for initially selected)
	FString GetDisplayString() const;

	// return EditedAttributeName's DisplayName (as text for widget callback)
	FText GetDisplayStringAsText() const;


	/** Delegate that is invoked when the selected item in the combo box changes */
	FOnAttributeNameChanged OnAttributeNameChanged;

};
