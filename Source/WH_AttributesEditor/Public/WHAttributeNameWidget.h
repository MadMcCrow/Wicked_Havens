/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeName.h"
#include "Widgets/SBoxPanel.h"


class SWHAttributeNameWidget : public SVerticalBox
{
public:
	//DECLARE_DELEGATE_OneParam(FOnAttributeNameChanged, FWHAttributeName);
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

	void UpdateAttributeOptions();

	// Internal Edited Attribute :
	FWHAttributeName EditedAttributeName;

	TArray<TSharedPtr<FString>> AttributeNameOptions;
	TArray<FString> AttributeNameOptionStrings;

	// Stored here to give pointer to it
	FString DisplayedString;

	void OnTextSelectionChanged(TSharedPtr<FString> String, ESelectInfo::Type Arg);

	TSharedPtr<FString> GetNameDisplayString() const;
	FText GetGUIDisplayString() const;

	/** Delegate that is invoked when the selected item in the combo box changes */
	FOnAttributeSelectionChanged OnSelectionChanged;

};
