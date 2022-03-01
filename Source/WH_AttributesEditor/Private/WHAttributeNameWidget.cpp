/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNameWidget.h"
#include "DetailLayoutBuilder.h"
#include "SSearchableComboBox.h"
#include "WHAttributeSettings.h"

#define LOCTEXT_NAMESPACE "SWHAttributeNameWidget"

TSharedRef<SWidget> SWHAttributeNameWidget::MakeComboEntryWidget(TSharedPtr<FString> InString) const
{
	return SNew(STextBlock).Text(FText::FromString(*InString.Get()));
}

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
		.OnGenerateWidget(this, &SWHAttributeNameWidget::MakeComboEntryWidget)
		.InitiallySelectedItem(MakeShared<FString>(DisplayedString))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &SWHAttributeNameWidget::GetTextDisplayString)
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
		const FString ValueString = String.ToSharedRef().Get();
		const FWHAttributeName NewAttributeName = FName(ValueString);
		if (Set(NewAttributeName))
		{
			OnSelectionChanged.ExecuteIfBound(MakeShared<FWHAttributeName>(EditedAttributeName), Arg);
		}
	}

}

FText SWHAttributeNameWidget::GetGUIDisplayString() const
{
	if (EditedAttributeName.IsValid())
	{
		return FText::FromString(EditedAttributeName.IDString());
	}
	return LOCTEXT("InvalidAttributeNameGUID", "Invalid Attribute Name");
}

FText SWHAttributeNameWidget::GetTextDisplayString() const
{
	return FText::FromString(DisplayedString);
}

#undef LOCTEXT_NAMESPACE
