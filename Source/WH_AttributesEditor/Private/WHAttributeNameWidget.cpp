 /* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNameWidget.h"
#include "DetailLayoutBuilder.h"
#include "SSearchableComboBox.h"
#include "WHAttributeSubsystem.h"

#define LOCTEXT_NAMESPACE "SWHAttributeNameWidget"

TSharedRef<SWidget> SWHAttributeNameWidget::MakeComboEntryWidget(TSharedPtr<FString> InString) const
{
	return SNew(STextBlock).Text(FText::FromString(*InString.Get()));
}

void SWHAttributeNameWidget::Construct(const FArguments& InArgs)
{
	EditedAttributeName = InArgs._AtributeName;

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
		.InitiallySelectedItem(MakeShared<FString>(GetDisplayString()))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &SWHAttributeNameWidget::GetDisplayStringAsText)
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

void SWHAttributeNameWidget::UpdateAttributeOptions()
{
	// Attributes stored in Us this :
	AttributeNameOptionStrings.Empty();
	AttributeNameOptions.Empty();

	// Settings :
	TArray<FName> AttributeNames;
	UWHAttributeSubsystem::GetAllNames(AttributeNames);

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
		const auto NewAttributeName = FName(ValueString);
		if (NewAttributeName.IsValid())
		{
			OnSelectionChanged.ExecuteIfBound(MakeShared<FWHAttributeName>(NewAttributeName), Arg);
		}
	}
}

FText SWHAttributeNameWidget::GetGUIDisplayString() const
{
	const auto AttributeNameValue = EditedAttributeName.Get();
	if (AttributeNameValue.IsValid())
	{
		return FText::FromString(AttributeNameValue.ExportIDString());
	}
	return LOCTEXT("InvalidAttributeNameGUID", "Invalid Attribute Name");
}

FString SWHAttributeNameWidget::GetDisplayString() const
{
	if (EditedAttributeName.IsSet())
	{
		return EditedAttributeName.Get().GetName().ToString();
	}
	return FString();
}

FText SWHAttributeNameWidget::GetDisplayStringAsText() const
{
	if (EditedAttributeName.IsSet())
	{
		return FText::FromName(EditedAttributeName.Get().GetName());
	}
	return LOCTEXT("InvalidAttributeName", "Invalid Attribute Name");
}

#undef LOCTEXT_NAMESPACE
