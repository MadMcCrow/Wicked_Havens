 /* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeTypeWidget.h"
#include "DetailLayoutBuilder.h"
#include "SPinTypeSelector.h"

#define LOCTEXT_NAMESPACE "SWHAttributeTypeWidget"

/** Get pin type */
FEdGraphPinType AttributeTypeToPinType(const FWHAttributeType& Type)
{
	FEdGraphPinType PinType;
	PinType.ResetToDefaults();
	PinType.PinCategory = NAME_None;
	return PinType;
}

/** Set from Graph pin */
bool PinTypeToAttributeType(const FEdGraphPinType& InPinType, FWHAttributeType& OutType)
{
	return false;
}



class FWHAttributeTypePinTypeSelectorFilter : public IPinTypeSelectorFilter
{
	public:
	FWHAttributeTypePinTypeSelectorFilter()
	{
	}

	virtual bool ShouldShowPinTypeTreeItem(FPinTypeTreeItem InItem) const override
	{
		if (!InItem.IsValid())
		{
			return false;
		}
		// Only allow types that can make attributes
		FWHAttributeType OutType;
		return PinTypeToAttributeType(InItem.Get()->GetPinType(false), OutType);
	}
};


 FEdGraphPinType SWHAttributeTypeWidget::OnGetPinInfo() const
 {
	return AttributeTypeToPinType(EditedAttributeType.Get());
 }

void SWHAttributeTypeWidget::Construct(const FArguments& InArgs)
{
	EditedAttributeType  = InArgs._AttributeType;
	OnAttributeTypeChanged = InArgs._OnAttributeTypeChanged;

 	TSharedPtr<IPinTypeSelectorFilter> CustomPinTypeFilter = MakeShared<FWHAttributeTypePinTypeSelectorFilter>();
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Add type box
	ChildSlot
	//.SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left)
	[
		SNew(SPinTypeSelector, FGetPinTypeTree::CreateUObject(K2Schema, &UEdGraphSchema_K2::GetVariableTypeTree))
			.TargetPinType(this, &SWHAttributeTypeWidget::OnGetPinInfo)
			.OnPinTypeChanged(this, &SWHAttributeTypeWidget::OnPinTypeChanged)
			.Schema(K2Schema)
			.TypeTreeFilter(ETypeTreeFilter::None)
			.bAllowArrays(true)
			.IsEnabled(true)
			.CustomFilter(CustomPinTypeFilter)
			.Font(IDetailLayoutBuilder::GetDetailFont())
	];
}

void SWHAttributeTypeWidget::OnPinTypeChanged(const FEdGraphPinType& NewPinType) const
{
	FWHAttributeType NewType;
	if (PinTypeToAttributeType(NewPinType, NewType))
	{
		OnAttributeTypeChanged.ExecuteIfBound(MakeShared<FWHAttributeType>(NewType));
	}

}

#undef LOCTEXT_NAMESPACE
