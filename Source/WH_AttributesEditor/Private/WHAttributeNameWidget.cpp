/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNameWidget.h"
#include "DetailLayoutBuilder.h"
#include "SSearchableComboBox.h"
#include "WHAttributeSettings.h"

#define LOCTEXT_NAMESPACE "SWHAttributeNameWidget"

void SWHAttributeNameWidget::Construct(const FArguments& InArgs)
{
	// Set
	Set(InArgs._AtributeName);
	OnSelectionChanged = InArgs._OnSelectionChanged;

	// Update attribute suggestion list
	UpdateAttributeOptions();

	// Add selection box
	AddSlot()
	.AutoHeight()
	[
		SNew(SSearchableComboBox)
		.OptionsSource(&AttributeNameOptions)
		.OnSelectionChanged(this, &SWHAttributeNameWidget::OnTextSelectionChanged)
		.InitiallySelectedItem(GetNameDisplayString())
		.Content()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("AttributeName", "Attribute Name"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];

	// Add GUID text box
	AddSlot()
	.AutoHeight()
		[
			// Add an object entry box.  Even though this isn't an object entry, we will simulate one
			SNew(SEditableTextBox)
			.Text(this, &SWHAttributeNameWidget::GetGUIDisplayString)
			.IsEnabled(false)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		];
}

bool SWHAttributeNameWidget::Set(const FWHAttributeName& AttributeName)
{
	if (AttributeName.IsValid())
	{
		EditedAttributeName = AttributeName;
		DisplayedString		= EditedAttributeName.GetName().ToString();
		return true;
	}
	// invalid :
	DisplayedString = FString();
	return false;
}


void SWHAttributeNameWidget::UpdateAttributeOptions()
{
	// Attributes stored in Us this :
	AttributeNameOptionStrings.Empty();
	AttributeNameOptions.Empty();

	// Settings :
	TArray<FName> AttributeNames;
	if (const auto Settings = GetDefault<UWHAttributeSettings>())
	{
		Settings->GetAllNames(AttributeNames);
	}

	// Update from what we found from settings
	for (const auto &NameItr : AttributeNames)
	{
		FString& StringNameAdded = AttributeNameOptionStrings.Add_GetRef(NameItr.ToString());
		AttributeNameOptions.Add(MakeShared<FString>(StringNameAdded));
	}
}

void SWHAttributeNameWidget::OnTextSelectionChanged(TSharedPtr<FString> String, ESelectInfo::Type Arg)
{
	if (String.IsValid())
	{
		if (Set(FWHAttributeName(FName(*String.Get()))))
		{
			OnSelectionChanged.ExecuteIfBound(MakeShared<FWHAttributeName>(EditedAttributeName), Arg);
		}
	}

}

TSharedPtr<FString> SWHAttributeNameWidget::GetNameDisplayString() const
{
	return MakeShared<FString>(DisplayedString);
}

FText SWHAttributeNameWidget::GetGUIDisplayString() const
{
	if (EditedAttributeName.IsValid())
	{
		return FText::FromString(EditedAttributeName.IDString());
	}
	return LOCTEXT("InvalidAttributeNameGUID", "Invalid Attribute Name");
}
