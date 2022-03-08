/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeType.h"
#include "Widgets/Layout/SBorder.h"

/**
 *	@class SWHAttributeTypeWidget
 *	An editor widget to display an attribute Type for editing by the user
 *	@see @struct FWHAttributeType
 */
class SWHAttributeTypeWidget : public SBorder
{
public:
	DECLARE_DELEGATE_OneParam(FOnAttributeTypeChanged, TSharedPtr<FWHAttributeType>);

	SLATE_BEGIN_ARGS(SWHAttributeTypeWidget)
			: _AttributeType(FWHAttributeType())
	{
		_Visibility = EVisibility::SelfHitTestInvisible;
	}
	SLATE_ATTRIBUTE(FWHAttributeType, AttributeType)
	SLATE_EVENT(FOnAttributeTypeChanged, OnAttributeTypeChanged)
SLATE_END_ARGS()

	FEdGraphPinType OnGetPinInfo() const;

	void Construct(const FArguments& InArgs);

private:

	// Internal Edited Attribute ;
	TAttribute<FWHAttributeType> EditedAttributeType;

	// Callback for when value changes :
	FOnAttributeTypeChanged OnAttributeTypeChanged;

	/** On Pin changed, ie. when we have to change type */
	void OnPinTypeChanged(const FEdGraphPinType& EdGraphPin) const;
};
