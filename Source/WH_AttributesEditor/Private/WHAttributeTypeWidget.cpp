 /* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeTypeWidget.h"
#include "DetailLayoutBuilder.h"
#include "SPinTypeSelector.h"

#define LOCTEXT_NAMESPACE "SWHAttributeTypeWidget"

/** Get pin type */
FEdGraphPinType AttributeTypeToPinType(const FWHAttributeType& Type)
{
	FEdGraphPinType PinType;
	PinType.ResetToDefaults();
	PinType.PinCategory = NAME_None;

	FString CurrentCPPType = Type.CPPType;
	if (auto ArrayType = Type.GetArrayBaseType())
	{
		PinType.ContainerType = EPinContainerType::Array;
		CurrentCPPType = ArrayType.GetValue();
	}
	else
	{
		PinType.ContainerType = EPinContainerType::None;
	}

	if (CurrentCPPType == TEXT("bool"))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Boolean;
	}
	else if (CurrentCPPType == TEXT("int32"))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Int;
	}
	else if (CurrentCPPType == TEXT("float"))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Real;
		PinType.PinSubCategory = UEdGraphSchema_K2::PC_Float;
	}
	else if (CurrentCPPType == TEXT("double"))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Real;
		PinType.PinSubCategory = UEdGraphSchema_K2::PC_Double;
	}
	else if (CurrentCPPType == TEXT("FName"))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Name;
	}
	else if (CurrentCPPType == TEXT("FString"))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_String;
	}
	else if (Cast<UScriptStruct>(Type.CPPTypeObject))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
		PinType.PinSubCategoryObject = Type.CPPTypeObject;
	}
	else if (Cast<UEnum>(Type.CPPTypeObject))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Byte;
		PinType.PinSubCategoryObject = Type.CPPTypeObject;
	}
	else if (Cast<UClass>(Type.CPPTypeObject))
	{
		PinType.PinCategory = UEdGraphSchema_K2::PC_Object;
		PinType.PinSubCategoryObject = Type.CPPTypeObject;
	}
	return PinType;
}

/** Set from Graph pin */
bool PinTypeToAttributeType(const FEdGraphPinType& InPinType, FWHAttributeType& OutType)
{
	FString Prefix = "";
	FString Suffix = "";
	if (InPinType.ContainerType == EPinContainerType::Array)
	{
		Prefix = TEXT("TArray<");
		Suffix = TEXT(">");
	}
	OutType.CPPType = FString();
	OutType.CPPTypeObject = nullptr;
	if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Boolean)
	{
		OutType.CPPType = Prefix + TEXT("bool") + Suffix;
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Int)
	{
		OutType.CPPType = Prefix + TEXT("int32") + Suffix;
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Real)
	{
		if (InPinType.PinSubCategory == UEdGraphSchema_K2::PC_Float)
		{
			OutType.CPPType = Prefix + TEXT("float") + Suffix;
		}
		else if (InPinType.PinSubCategory == UEdGraphSchema_K2::PC_Double)
		{
			OutType.CPPType = Prefix + TEXT("double") + Suffix;
		}
		else
		{
			checkf(false, TEXT("Unexpected subcategory for PC_Real pin type."));
		}
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Float)
	{
		OutType.CPPType = Prefix + TEXT("float") + Suffix;
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Double)
	{
		OutType.CPPType = Prefix + TEXT("double") + Suffix;
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Name)
	{
		OutType.CPPType = Prefix + TEXT("FName") + Suffix;
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_String)
	{
		OutType.CPPType = Prefix + TEXT("FString") + Suffix;
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		if (UScriptStruct* Struct = Cast<UScriptStruct>(InPinType.PinSubCategoryObject))
		{
			OutType.CPPType = Prefix + *Struct->GetStructCPPName() + Suffix;
			OutType.CPPTypeObject = Struct;
		}
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Object ||
		InPinType.PinCategory == UEdGraphSchema_K2::PC_SoftObject ||
		InPinType.PinCategory == UEdGraphSchema_K2::AllObjectTypes)
	{
		if (UClass* Class = Cast<UClass>(InPinType.PinSubCategoryObject))
		{
			OutType.CPPType = Prefix + FString::Printf(TEXT("TObjectPtr<%s%s>"), Class->GetPrefixCPP(), *Class->GetName()) + Suffix;
			OutType.CPPTypeObject = Class;
		}
	}
	else if (InPinType.PinCategory == UEdGraphSchema_K2::PC_Byte ||
		InPinType.PinCategory == UEdGraphSchema_K2::PC_Enum)
	{
		if (UEnum* Enum = Cast<UEnum>(InPinType.PinSubCategoryObject))
		{
			OutType.CPPType = Prefix + Enum->GetFName().ToString() + Suffix;
			OutType.CPPTypeObject = Enum;
		}
		else
		{
			OutType.CPPType = Prefix + TEXT("uint8") + Suffix;
		}
	}
	else
	{
		return false;
	}
	return true;
}


class FWHAttributeTypePinTypeSelectorFilter : public IPinTypeSelectorFilter
{
	public:
	FWHAttributeTypePinTypeSelectorFilter()
	{
	}

	virtual bool ShouldShowPinTypeTreeItem(FPinTypeTreeItem InItem) const override
	{
		if (!InItem.IsValid())
		{
			return false;
		}
		// Only allow types that can make attributes
		FWHAttributeType OutType;
		return PinTypeToAttributeType(InItem.Get()->GetPinType(false), OutType);
	}
};


 FEdGraphPinType SWHAttributeTypeWidget::OnGetPinInfo() const
 {
	return AttributeTypeToPinType(EditedAttributeType.Get());
 }

void SWHAttributeTypeWidget::Construct(const FArguments& InArgs)
{
	EditedAttributeType  = InArgs._AttributeType;
	OnAttributeTypeChanged = InArgs._OnAttributeTypeChanged;

 	TSharedPtr<IPinTypeSelectorFilter> CustomPinTypeFilter = MakeShared<FWHAttributeTypePinTypeSelectorFilter>();
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Add type box
	ChildSlot
	//.SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left)
	[
		SNew(SPinTypeSelector, FGetPinTypeTree::CreateUObject(K2Schema, &UEdGraphSchema_K2::GetVariableTypeTree))
			.TargetPinType(this, &SWHAttributeTypeWidget::OnGetPinInfo)
			.OnPinTypeChanged(this, &SWHAttributeTypeWidget::OnPinTypeChanged)
			.Schema(K2Schema)
			.TypeTreeFilter(ETypeTreeFilter::None)
			.bAllowArrays(true)
			.IsEnabled(true)
			.CustomFilter(CustomPinTypeFilter)
			.Font(IDetailLayoutBuilder::GetDetailFont())
	];
}

void SWHAttributeTypeWidget::OnPinTypeChanged(const FEdGraphPinType& NewPinType) const
{
	FWHAttributeType NewType;
	if (PinTypeToAttributeType(NewPinType, NewType))
	{
		OnAttributeTypeChanged.ExecuteIfBound(MakeShared<FWHAttributeType>(NewType));
	}

}

#undef LOCTEXT_NAMESPACE
