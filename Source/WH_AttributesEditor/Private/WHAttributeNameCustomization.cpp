/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNameCustomization.h"
#include "DetailLayoutBuilder.h"
#include "PropertyCustomizationHelpers.h"
#include "PropertyHandle.h"
#include "SSearchableComboBox.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "WHAttributeContainer.h"
#include "WHAttributeNameWidget.h"
#include "WHAttributeSettings.h"


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
			.OnSelectionChanged(this,  &FWHAttributeNameCustomization::OnAttributeChanged)
		];

	// This avoids making duplicate reset boxes
	AttributeNamePropertyHandle->MarkResetToDefaultCustomized();
}

void FWHAttributeNameCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                      IDetailChildrenBuilder& StructBuilder,
                                                      IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}


void FWHAttributeNameCustomization::OnAttributeChanged(TSharedPtr<FWHAttributeName> NewName, ESelectInfo::Type Arg) const
{
	if (NewName.IsValid() && NewName.Get()->IsValid())
	{
		if (AttributeNamePropertyHandle.IsValid())
		{
			TArray<void*> RawData;
			AttributeNamePropertyHandle->AccessRawData(RawData);
			AttributeNamePropertyHandle->NotifyPreChange();
			for (auto RawDataInstance : RawData)
			{
				*(FWHAttributeName*)RawDataInstance =  *NewName.Get();
			}
			AttributeNamePropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
			AttributeNamePropertyHandle->NotifyFinishedChangingProperties();
		}
	}
}
#undef LOCTEXT_NAMESPACE
