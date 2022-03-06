/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNamePin.h"
#include "WHAttributeContainer.h"
#include "NodeFactory.h"
#include "WHAttributeNameWidget.h"

#define LOCTEXT_NAMESPACE "WHAttributeNamePin"

// an obviously invalid name, for export functions in need of a default value
static const FWHAttributeName DefaultName;

void SWHAttributeNamePin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	bOnlyShowDefaultValue = false;
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget>	SWHAttributeNamePin::GetDefaultValueWidget()
{
	// Check that graph pin is valid
	if (GraphPinObj == nullptr)
	{
		return SNullWidget::NullWidget;
	}

	// Get Schema
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	if (Schema == nullptr)
	{
		return SNullWidget::NullWidget;
	}

	return	SNew(SWHAttributeNameWidget)
	.AtributeName(this,  &SWHAttributeNamePin::GetDefaultAttributeName)
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
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	if (Schema != nullptr)
	{
		if (NewAttributeName.IsValid())
		{
			const auto ExportString = FWHAttributeName::Export(*NewAttributeName.Get());
			if (!Schema->DoesDefaultValueMatch(*GraphPinObj, ExportString))
			{
				const FScopedTransaction Transaction( LOCTEXT("PinAttributeChanged", "Change Attribute Pin Value"));
				GraphPinObj->Modify();
				Schema->TrySetDefaultValue(*GraphPinObj,ExportString);
			}
		}
	}

}

FWHAttributeName SWHAttributeNamePin::GetDefaultAttributeName() const
{
	if(GraphPinObj->IsPendingKill())
	{
		return FWHAttributeName();
	}
	return FWHAttributeName::Import(GraphPinObj->GetDefaultAsString());
}

FString SWHAttributeNamePin::GetAttributeNameAsString() const
{
	return GetDefaultAttributeName().GetName().ToString();
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
