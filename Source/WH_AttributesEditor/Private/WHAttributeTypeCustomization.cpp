/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeTypeCustomization.h"
#include "PropertyCustomizationHelpers.h"
#include "PropertyHandle.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "WHAttributeTypeWidget.h"


#define LOCTEXT_NAMESPACE "WHAttributeTypeCustomization"


void FWHAttributeTypeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                    FDetailWidgetRow& HeaderRow,
                                                    IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	AttributeTypePropertyHandle = InStructPropertyHandle;
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
			SNew(SWHAttributeTypeWidget)
			.OnAttributeTypeChanged(this,  &FWHAttributeTypeCustomization::OnAttributeTypeChanged)
			.AttributeType(this,  &FWHAttributeTypeCustomization::GetEditedAttributeType)
		];

	// This avoids making duplicate reset boxes
	AttributeTypePropertyHandle->MarkResetToDefaultCustomized();
}

void FWHAttributeTypeCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                      IDetailChildrenBuilder& StructBuilder,
                                                      IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

FWHAttributeType FWHAttributeTypeCustomization::GetEditedAttributeType() const
{
	if (AttributeTypePropertyHandle.IsValid())
	{
		void* StructData;
		if (AttributeTypePropertyHandle->GetValueData(StructData) == FPropertyAccess::Success)
		{
			FWHAttributeType* WHAttributeNamePtr = reinterpret_cast<FWHAttributeType*>(StructData);
			return *WHAttributeNamePtr;
		}
	}
	return FWHAttributeType();
}


void FWHAttributeTypeCustomization::OnAttributeTypeChanged(TSharedPtr<FWHAttributeType> NewType) const
{
	if (NewType.IsValid() && NewType.Get())
	{
		const FWHAttributeType InputAttribute = *NewType.Get();
		if (AttributeTypePropertyHandle.IsValid())
		{
			TArray<void*> RawData;
			AttributeTypePropertyHandle->AccessRawData(RawData);
			AttributeTypePropertyHandle->NotifyPreChange();
			//AttributeTypePropertyHandle->SetValueFromFormattedString(FWHAttributeType::Export(InputAttribute));
			// No need for that nonsense
			{
				*(FWHAttributeType*)RawData[0] = InputAttribute;
			}
			AttributeTypePropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
			AttributeTypePropertyHandle->NotifyFinishedChangingProperties();
		}
	}
}


#undef LOCTEXT_NAMESPACE
