/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeRefCustomization.h"
#include "DetailWidgetRow.h"
#include "WHAttributeRefWidget.h"

#define LOCTEXT_NAMESPACE "WHAttributeRefCustomization"

void FWHAttributeRefCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle,
	FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	AttributeRefPropertyHandle = InStructPropertyHandle;
	auto EmptyString =  FName(NAME_None).ToString();
	// Set widget :
	HeaderRow
		.NameContent()
		[
			InStructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(250.0f)
		.MaxDesiredWidth(0.0f)
		[
			SNew(SWHAttributeRefWidget)
			.OnAttributeRefChanged(this,  &FWHAttributeRefCustomization::OnAttributeRefChanged)
			.AttributeRef(this,  &FWHAttributeRefCustomization::GetEditedAttributeRef)
		];

	// This avoids making duplicate reset boxes
	AttributeRefPropertyHandle->MarkResetToDefaultCustomized();
}

void FWHAttributeRefCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

FWHAttributeRef FWHAttributeRefCustomization::GetEditedAttributeRef() const
{
	if (AttributeRefPropertyHandle.IsValid())
	{
		void* StructData;
		if (AttributeRefPropertyHandle->GetValueData(StructData) == FPropertyAccess::Success)
		{
			FWHAttributeRef* WHAttributeNamePtr = reinterpret_cast<FWHAttributeRef*>(StructData);
			return *WHAttributeNamePtr;
		}
	}
	return FWHAttributeRef();
}

void FWHAttributeRefCustomization::OnAttributeRefChanged(TSharedPtr<FWHAttributeRef> NewRef) const
{
	if (NewRef.IsValid() && NewRef.Get()->IsValid())
	{
		const auto InputAttribute = *NewRef.Get();
		if (AttributeRefPropertyHandle.IsValid())
		{
			const FScopedTransaction Transaction( LOCTEXT("AttributeRefDefaultChange", "Changed Attribute Ref default value"));
			AttributeRefPropertyHandle->SetValue(InputAttribute);
			AttributeRefPropertyHandle->NotifyPreChange();
			AttributeRefPropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
			AttributeRefPropertyHandle->NotifyFinishedChangingProperties();
		}
	}
}
#undef LOCTEXT_NAMESPACE