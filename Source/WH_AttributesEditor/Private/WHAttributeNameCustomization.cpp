/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNameCustomization.h"
#include "DetailLayoutBuilder.h"
#include "PropertyCustomizationHelpers.h"
#include "PropertyHandle.h"
#include "SSearchableComboBox.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "WHAttributeContainer.h"
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
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
			SNew(SSearchableComboBox)
			.OptionsSource(&AttributeNamesStrings)
			//.ComboBoxStyle()
			.OnSelectionChanged(this, &FWHAttributeNameCustomization::OnAttributeChanged)
			.InitiallySelectedItem(TSharedPtr<FString>(&EmptyString))
			.Content()
				[
				SNew(STextBlock)
				.Text(LOCTEXT("AttributeName", "Attribute Name"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				// Add an object entry box.  Even though this isn't an object entry, we will simulate one
				SNew(SEditableTextBox)
				.Text(this, &FWHAttributeNameCustomization::GetAttributeGUID)
				.IsEnabled(false)
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		];

	// This avoids making duplicate reset boxes
	AttributeNamePropertyHandle->MarkResetToDefaultCustomized();
}

void FWHAttributeNameCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                      IDetailChildrenBuilder& StructBuilder,
                                                      IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}


void FWHAttributeNameCustomization::UpdateFromAttributeList()
{
	TArray<FName> AttributeNames;
	TArray<FString> AttributeStrings;
	if (auto Settings = GetDefault<UWHAttributeSettings>())
	{
		Settings->GetAllNames(AttributeNames);
	}
	// Add none as an option, and make that first !
	AttributeNames.Insert(NAME_None, 0);
	// Add all names as strings
	for (auto NameItr: AttributeNames)
	{
		// not sure about this :/
		AttributeNamesStrings.Add(TSharedPtr<FString>(&AttributeStrings.Add_GetRef(NameItr.ToString())));
	}
}

FText FWHAttributeNameCustomization::GetAttributeGUID() const
{
	static const FText ErrorText = LOCTEXT("InvalidWHAttributeName", "Invalid Attribute Name");
	if (AttributeNamePropertyHandle.IsValid())
	{
		TArray<void*> RawData;
		AttributeNamePropertyHandle->AccessRawData(RawData);
		if (RawData.Num() != 1)
		{
			return ErrorText;
		}
		const auto AttributePtr = static_cast<FWHAttributeName*>(RawData[0]);
		if (!AttributePtr)
		{
			return ErrorText;
		}
		return FText::FromString(AttributePtr->IDString());
	}
	return ErrorText;
}

void FWHAttributeNameCustomization::OnAttributeChanged(TSharedPtr<FString, ESPMode::Fast> String, ESelectInfo::Type Arg) const
{
	const auto Name = FName(*(String.Get()));
	const FWHAttributeName FoundAttribute = FWHAttributeName(Name);
	const bool bInputValid = FoundAttribute.IsValid();

	if (bInputValid && AttributeNamePropertyHandle.IsValid())
	{
		TArray<void*> RawData;
		AttributeNamePropertyHandle->AccessRawData(RawData);
		AttributeNamePropertyHandle->NotifyPreChange();
		for (auto RawDataInstance : RawData)
		{
			*(FWHAttributeName*)RawDataInstance = FoundAttribute;
		}
		AttributeNamePropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
		AttributeNamePropertyHandle->NotifyFinishedChangingProperties();
	}
}
#undef LOCTEXT_NAMESPACE
