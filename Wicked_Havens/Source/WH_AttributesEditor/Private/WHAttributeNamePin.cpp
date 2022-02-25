/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeNamePin.h"
#include "WHAttributeContainer.h"
#include "WHAttributeSettings.h"
#include "DetailLayoutBuilder.h"
#include "NodeFactory.h"
#include "SSearchableComboBox.h"

#define LOCTEXT_NAMESPACE "WHAttributeNamePin"


void SWHAttributeNamePin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	AttributeNamesStrings.Empty();
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


	auto EmptyString =  FName(NAME_None).ToString();
	return	SNew(SVerticalBox)
   			+ SVerticalBox::Slot()
   			.AutoHeight()
   			[
   			SNew(SSearchableComboBox)
   			.OptionsSource(&AttributeNamesStrings)
   			.OnSelectionChanged(this, &SWHAttributeNamePin::OnAttributeChanged)
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
   				.Text(this, &SWHAttributeNamePin::GetAttributeGUID)
   				.IsEnabled(false)
   				.Font(IDetailLayoutBuilder::GetDetailFont())
   			];

	///return SGraphPinObject::GetDefaultValueWidget();

}

void SWHAttributeNamePin::OnAttributeChanged(TSharedPtr<FString> String, ESelectInfo::Type Arg)
{
	if(GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FString TypeValueString = *String.Get();
	CurrentAttribute = MakeShared<FWHAttributeName>(FWHAttributeName(FName(TypeValueString)));
	if (GraphPinObj->GetDefaultAsString() != TypeValueString)
	{
		GraphPinObj->Modify();
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, CurrentAttribute->GetName().ToString());
	}
}


void SWHAttributeNamePin::UpdateFromAttributeList()
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


FText SWHAttributeNamePin::GetAttributeGUID() const
{

	static const FText ErrorText = LOCTEXT("InvalidWHAttributeName", "Invalid Attribute Name");
	/*
	if(GraphPinObj->IsPendingKill())
	{
		return ErrorText;
	}

	return FText::FromString(CurrentAttribute->IDString());
	*/
	return ErrorText;
}


TSharedPtr<class SGraphPin> FWHAttributeNamePinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		const UScriptStruct* AttributeNameStruct = TBaseStructure<FWHAttributeName>::Get();
		if (InPin->PinType.PinSubCategoryObject == AttributeNameStruct)
		{
			TSharedPtr<SGraphPin> K2PinWidget = SNew(SWHAttributeNamePin, InPin);
			if (K2PinWidget.IsValid())
			{
				return K2PinWidget;
			}
		}
	}
	return  FNodeFactory::CreateK2PinWidget(InPin);
}
#undef LOCTEXT_NAMESPACE
