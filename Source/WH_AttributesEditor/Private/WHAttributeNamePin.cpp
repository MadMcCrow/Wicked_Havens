/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNamePin.h"
#include "WHAttributeContainer.h"
#include "WHAttributeSettings.h"
#include "DetailLayoutBuilder.h"
#include "NodeFactory.h"
#include "WHAttributeNameWidget.h"

#define LOCTEXT_NAMESPACE "WHAttributeNamePin"


void SWHAttributeNamePin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	bOnlyShowDefaultValue = false;
	SGraphPinObject::Construct(SGraphPinObject::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget>	SWHAttributeNamePin::GetDefaultValueWidget()
{
	if (GraphPinObj == nullptr)
	{
		return SNullWidget::NullWidget;
	}

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();

	if (Schema == nullptr)
	{
		return SNullWidget::NullWidget;
	}

	if(ShouldDisplayAsSelfPin())
	{
		return SNew(SEditableTextBox)
			.Style( FEditorStyle::Get(), "Graph.EditableTextBox" )
			.Text( this, &SWHAttributeNamePin::GetValue )
			.SelectAllTextWhenFocused(false)
			.Visibility( this, &SGraphPinObject::GetDefaultValueVisibility )
			.IsReadOnly( true )
			.ForegroundColor( FSlateColor::UseForeground() );
	}


	return	SNew(SWHAttributeNameWidget)
	.AtributeName(DefaultAttributeName)
	.Visibility( this, &SGraphPinObject::GetDefaultValueVisibility )
	.OnSelectionChanged(this, &SWHAttributeNamePin::OnAttributeChanged);
}

void SWHAttributeNamePin::OnAttributeChanged(TSharedPtr<FWHAttributeName> NewAttributeName, ESelectInfo::Type Arg)
{
	if(GraphPinObj->IsPendingKill())
	{
		return;
	}

	// Update value :
	DefaultAttributeName = *NewAttributeName.Get();

	// Set default value from that string representation
	if (GraphPinObj->GetDefaultAsString() != GetAttributeNameAsString())
	{
		GraphPinObj->Modify();
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, GetAttributeNameAsString());
	}
}

FString SWHAttributeNamePin::GetAttributeNameAsString() const
{
	return DefaultAttributeName.GetName().ToString();
}


TSharedPtr<class SGraphPin, ESPMode::ThreadSafe> FWHAttributeNamePinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		const UScriptStruct* AttributeNameStruct = TBaseStructure<FWHAttributeName>::Get();
		if (InPin->PinType.PinSubCategoryObject == AttributeNameStruct)
		{
			TSharedPtr<SGraphPin,ESPMode::ThreadSafe> K2PinWidget = SNew(SWHAttributeNamePin, InPin);
			if (K2PinWidget.IsValid())
			{
				return K2PinWidget;
			}
		}
	}
	return  FNodeFactory::CreateK2PinWidget(InPin);
}
#undef LOCTEXT_NAMESPACE
