/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeRefWidget.h"
#include "PropertyCustomizationHelpers.h"
#include "DetailWidgetRow.h"
#include "WHAttribute.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

void SWHAttributeRefWidget::Construct(const FArguments& InArgs)
{
	EditedAttributeRef = InArgs._AttributeRef;
	OnAttributeNameChanged = InArgs._OnAttributeRefChanged;
	

	// Add selection box
	AddSlot()
	.AutoHeight()
	[
	SNew(SClassPropertyEntryBox)
		.MetaClass(UWHAttributeBase::StaticClass())
		.AllowAbstract(false)
		.IsBlueprintBaseOnly(false)
		.AllowNone(false)
		.ShowTreeView(true)
		.HideViewOptions(true)
		.ShowDisplayNames(true)
		.SelectedClass(this, &SWHAttributeRefWidget::GetAttributeClass)
		.OnSetClass(this, &SWHAttributeRefWidget::OnSetAttributeClass)
		
	];
}

FString SWHAttributeRefWidget::GetAttributeString() const
{
	if (EditedAttributeRef.IsBound())
	{
		return EditedAttributeRef.Get().ToString();
	}
	return FString();
}

FText SWHAttributeRefWidget::GetAttributeStringAsText() const
{
	return FText::FromString(GetAttributeString());
}

const UClass* SWHAttributeRefWidget::GetAttributeClass() const
{
	if (EditedAttributeRef.IsBound())
	{
		return EditedAttributeRef.Get().GetAttributeClass();
	}
	return nullptr;
}

void SWHAttributeRefWidget::OnSetAttributeClass(const UClass* NewClass)
{
	if (!NewClass)
		return;
		
	if (EditedAttributeRef.IsBound())
	{
		if (NewClass->IsChildOf<UWHAttributeBase>())
		{
			const FWHAttributeRef NewAttributeRef = FWHAttributeRef(NewClass);
			if (NewAttributeRef.IsValid())
			{
				// should we do this :
				EditedAttributeRef.Set(NewAttributeRef);
				// Execute event
				OnAttributeNameChanged.ExecuteIfBound(MakeShared<FWHAttributeRef>(NewAttributeRef));
			}
		}
	}
}


