/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeName.h"
#include "Widgets/SBoxPanel.h"

/**
 *	@class SWHAttributeNameWidget
 *	An editor widget to display an attribute name for editing by the user
 *	@see @struct FWHAttributeName
 */
class SWHAttributeNameWidget : public SVerticalBox
{
public:
	typedef typename TSlateDelegates< TSharedPtr<FWHAttributeName> >::FOnSelectionChanged FOnAttributeSelectionChanged;

	SLATE_BEGIN_ARGS(SWHAttributeNameWidget)
		: _AtributeName(FWHAttributeName())
		, _OnSelectionChanged()
		{
			_Visibility = EVisibility::SelfHitTestInvisible;
		}
		SLATE_ARGUMENT(FWHAttributeName, AtributeName)
		SLATE_EVENT(FOnAttributeSelectionChanged, OnSelectionChanged)
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

	/**
	 *	Set from attribute name
	 */
	bool Set(const FWHAttributeName& AttributeName);


private:
	// Calls the settings to obtain a list of all the Attributes currently available
	void UpdateAttributeOptions();

	// Internal Edited Attribute :
	FWHAttributeName EditedAttributeName;

	// Stores the Attribute options
	TArray<FString> AttributeNameOptionStrings;
	// Store pointers to the strings just before.
	TArray<TSharedPtr<FString>> AttributeNameOptions;

	// Stored here to give pointer to it
	FString DisplayedString;

	// Called when user selects an entry
	void OnTextSelectionChanged(TSharedPtr<FString> String, ESelectInfo::Type Arg);

	// Called when we need to generate entries
	TSharedRef<SWidget> MakeComboEntryWidget(TSharedPtr<FString> InString) const;

	// return the Selected Attribute GUID (as text for widget callback)
	FText GetGUIDisplayString() const;

	// return DisplayedString  (as text for widget callback)
	FText GetTextDisplayString() const;

	/** Delegate that is invoked when the selected item in the combo box changes */
	FOnAttributeSelectionChanged OnSelectionChanged;

};
