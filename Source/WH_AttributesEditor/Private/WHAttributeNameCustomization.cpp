/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNameCustomization.h"
#include "PropertyCustomizationHelpers.h"
#include "PropertyHandle.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "WHAttributeNameWidget.h"


#define LOCTEXT_NAMESPACE "WHAttributeNameCustomization"


void FWHAttributeNameCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                    FDetailWidgetRow& HeaderRow,
                                                    IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	AttributeNamePropertyHandle = InStructPropertyHandle;
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
			SNew(SWHAttributeNameWidget)
			.OnAttributeNameChanged(this,  &FWHAttributeNameCustomization::OnAttributeNameChanged)
			.AttributeName(this,  &FWHAttributeNameCustomization::GetEditedAttributeName)
		];

	// This avoids making duplicate reset boxes
	AttributeNamePropertyHandle->MarkResetToDefaultCustomized();
}

void FWHAttributeNameCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                      IDetailChildrenBuilder& StructBuilder,
                                                      IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}


void FWHAttributeNameCustomization::OnAttributeNameChanged(TSharedPtr<FWHAttributeName> NewName) const
{
	if (NewName.IsValid() && NewName.Get()->IsValid())
	{
		const auto InputAttribute = *NewName.Get();
		if (AttributeNamePropertyHandle.IsValid())
		{
			const FScopedTransaction Transaction( LOCTEXT("AttributeNameDefaultChange", "Changed Attribute Name default value"));
			TArray<void*> RawData;
			AttributeNamePropertyHandle->AccessRawData(RawData);
			AttributeNamePropertyHandle->NotifyPreChange();
			{
				*(FGuid*)RawData[0] = InputAttribute.GetID();
			}
			AttributeNamePropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
			AttributeNamePropertyHandle->NotifyFinishedChangingProperties();
		}
	}
}


FWHAttributeName FWHAttributeNameCustomization::GetEditedAttributeName() const
{
	if (AttributeNamePropertyHandle.IsValid())
	{
		void* StructData;
		if (AttributeNamePropertyHandle->GetValueData(StructData) == FPropertyAccess::Success)
		{
			FWHAttributeName* WHAttributeNamePtr = reinterpret_cast<FWHAttributeName*>(StructData);
			return *WHAttributeNamePtr;
		}
	}
	return FWHAttributeName();
}

#undef LOCTEXT_NAMESPACE
