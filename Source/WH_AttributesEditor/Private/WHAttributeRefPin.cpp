/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeRefPin.h"
#include "WHAttributeRefWidget.h"
#include "WHAttribute.h"
#include "NodeFactory.h"

#define LOCTEXT_NAMESPACE "WHAttributeRefPin"

void SWHAttributeRefPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	bOnlyShowDefaultValue = false;
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SWHAttributeRefPin::GetDefaultValueWidget()
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

	return	SNew(SWHAttributeRefWidget)
	.AttributeRef(this,  &SWHAttributeRefPin::GetDefaultAttributeRef)
	.Visibility( this, &SGraphPinObject::GetDefaultValueVisibility )
	.OnAttributeRefChanged(this, &SWHAttributeRefPin::OnAttributeRefChanged);
}

FSlateColor SWHAttributeRefPin::GetPinColor() const {return FSlateColor(FColor::Silver);}

void SWHAttributeRefPin::OnAttributeRefChanged(TSharedPtr<FWHAttributeRef> NewAttributeRef)
{
	if(GraphPinObj->IsPendingKill())
	{
		return;
	}

	// Update value :
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	if (Schema != nullptr)
	{
		if (NewAttributeRef.IsValid())
		{
			const auto ExportString = NewAttributeRef->ToString();
			if (!Schema->DoesDefaultValueMatch(*GraphPinObj, ExportString))
			{
				const FScopedTransaction Transaction( LOCTEXT("PinAttributeRefChanged", "Changed Attribute Ref Pin Value"));
				GraphPinObj->Modify();
				Schema->TrySetDefaultValue(*GraphPinObj,ExportString);
			}
		}
	}
}

FWHAttributeRef SWHAttributeRefPin::GetDefaultAttributeRef() const
{
	FWHAttributeRef Ref;
	Ref.Path = GraphPinObj->IsPendingKill() ? FString() : GraphPinObj->GetDefaultAsString();
	return Ref;
}

FString SWHAttributeRefPin::GetAttributeRefAsString() const
{
	return GetDefaultAttributeRef().ToString();
}

TSharedPtr<SGraphPin, ESPMode::ThreadSafe> FWHAttributeRefPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		const UScriptStruct* AttributeRefStruct = TBaseStructure<FWHAttributeRef>::Get();
		if (InPin->PinType.PinSubCategoryObject == AttributeRefStruct)
		{
			TSharedPtr<SGraphPin,ESPMode::ThreadSafe> K2PinWidget = SNew(SWHAttributeRefPin, InPin);
			if (K2PinWidget.IsValid())
			{
				return K2PinWidget;
			}
		}
	}
	return  FNodeFactory::CreateK2PinWidget(InPin);
}

#undef LOCTEXT_NAMESPACE