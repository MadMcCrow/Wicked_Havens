/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeValue.h"
#include "Widgets/SBoxPanel.h"

/**
 *	@class SWHAttributeValueWidget
 *	An editor widget to display an attribute name for editing by the user
 *	@see @struct FWHAttributeName
 */
class SWHAttributeValueWidget : public SVerticalBox
{
public:
		DECLARE_DELEGATE_OneParam(FOnAttributeChanged, TSharedPtr<FWHAttributeValue>);

	SLATE_BEGIN_ARGS(SWHAttributeValueWidget)
		: _AtributeValue(FWHAttributeValue())
		, _bShowTypeSelector(false)
		{
			_Visibility = EVisibility::SelfHitTestInvisible;
		}
		SLATE_ATTRIBUTE(FWHAttributeValue, AtributeValue)
		SLATE_ATTRIBUTE(bool, bShowTypeSelector)
		SLATE_EVENT(FOnAttributeChanged, OnTypeSelectionChange)
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

private:

	void CommitValue();

	// Internal Edited Attribute ;
	TAttribute<FWHAttributeValue> EditedAttributeValue;

	// Called when user input a text value
	template<typename NumericType>
	void OnNumericValueInputChanged(NumericType NumCommitted, ETextCommit::Type InArg)
	{
		const FWHAttributeValue NewValue = NumCommitted;
		EditedAttributeValue = NewValue;
		CommitValue();
	}

	// Called when user input a text value
	void OnTextValueInputChanged(const FText& TextCommitted, ETextCommit::Type InArg);

	void OnBoolValueChanged(ECheckBoxState CheckBoxState)
	{
		switch (CheckBoxState)
		{
		case ECheckBoxState::Unchecked:	EditedAttributeValue = false;	CommitValue(); return;
		case ECheckBoxState::Checked: EditedAttributeValue = true; 		CommitValue(); return;
		case ECheckBoxState::Undetermined:
		default: ;
		}

	}

	void OnColorCommitted(FLinearColor color)
	{
		const FWHAttributeValue NewValue = color;
		EditedAttributeValue = NewValue;
	}

	// Create the appropriate Widget to edit the property :
	TSharedRef<SWidget> MakeValueEntryWidget();

	// Callback for when value changes :
	FOnAttributeChanged OnTypeSelectionChange;
};
