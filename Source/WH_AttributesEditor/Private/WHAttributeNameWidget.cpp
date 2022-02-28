/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNameWidget.h"


void SWHAttributeNameWidget::Construct(const FArguments& InArgs)
{
	SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.AutoHeight()
	[
		SNew(SSearchableComboBox)
		.OptionsSource(&AttributeNamesStrings)
		//.ComboBoxStyle()
		.OnSelectionChanged(this, &SWHAttributeNameWidget::OnTextSelectionChanged)
		.InitiallySelectedItem(TSharedPtr<FString, ESPMode::ThreadSafe>(&EmptyString))
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
}


void SWHAttributeNameWidget::OnTextSelectionChanged(FText NewText)
{

}

FGuid SWHAttributeNameWidget::GetAttributeNameGuid() const
{
	
}