/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttribute.h"
#include "Widgets/SBoxPanel.h"

/**
 *	@class SWHAttributeRefWidget
 *	An editor widget to display an attribute name for editing by the user
 *	@see @struct SWHAttributeRefWidget
 */
class SWHAttributeRefWidget : public SVerticalBox
{
public:
	DECLARE_DELEGATE_OneParam(FOnAttributeRefChanged, TSharedPtr<FWHAttributeRef>);

	SLATE_BEGIN_ARGS(SWHAttributeRefWidget)
		: _AttributeRef(FWHAttributeRef())
		{
			_Visibility = EVisibility::SelfHitTestInvisible;
		}
		SLATE_ATTRIBUTE(FWHAttributeRef, AttributeRef)
		SLATE_EVENT(FOnAttributeRefChanged, OnAttributeRefChanged)
	SLATE_END_ARGS()
	

	void Construct(const FArguments& InArgs);

private:

	// Internal Edited Attribute ;
	TAttribute<FWHAttributeRef> EditedAttributeRef;

	// Stores the Attribute options
	TArray<FString> AttributeNameOptionStrings;
	
	// Store pointers to the strings just before.
	TArray<TSharedPtr<FString>> AttributeNameOptions;
	
	// return EditedAttributeName's DisplayName (as string for initially selected)
	FString GetAttributeString() const;

	// return EditedAttributeName's DisplayName (as text for widget callback)
	FText GetAttributeStringAsText() const;

	/** Delegate that is invoked when the selected item in the combo box changes */
	FOnAttributeRefChanged OnAttributeNameChanged;

	/** Get class from AttributeRef */
	const UClass* GetAttributeClass() const;

	void OnSetAttributeClass(const UClass* NewClass);
	
	
};
