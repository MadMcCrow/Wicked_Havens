/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WHAttributeContainer.h"
#include "WHAttributeSubsystem.h"
#include "WHAttributeType.h"
#include "UObject/Field.h"
#include "WHAttributeFunctionLibrary.generated.h"

/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="Inventory")
class WH_ATTRIBUTES_API UWHAttributeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**	Make and Break Functions for AttributeContainer */
	//UFUNCTION(BlueprintCallable, Category="Attributes|Containers", meta = (NativeBreakFunc))
	//static void BreakAttributeContainer(const FWHAttributeContainer& AttributeContainer,  TArray<FWHAttribute>& Attributes );
	//UFUNCTION(BlueprintPure, Category="Attributes|Containers", meta = (NativeMakeFunc))
	//static void MakeAttributeContainer(const TArray<FWHAttribute>& Attributes,  FWHAttributeContainer& AttributeContainer);


	UFUNCTION( BlueprintCallable, Category="Attributes", CustomThunk,meta = (CustomStructureParam = "Input"))
	static void SetAttribute(UField* Input, FWHAttribute& Attribute, bool &bResult);
	DECLARE_FUNCTION(execSetAttribute)
	{
		// Input Field property :
		Stack.Step(Stack.Object, NULL);		// Steps into the stack, walking to the next property in it
		FProperty* InputProperty = CastField<FProperty>(Stack.MostRecentProperty);// Grab the last property found when we walked the stack
		void* InputPtr = Stack.MostRecentPropertyAddress;// Grab the base address where the struct actually stores its data

		// Attribute
		Stack.Step(Stack.Object, NULL);
		FProperty* AttributeProperty = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* AttributePtr = Stack.MostRecentPropertyAddress;
		FWHAttribute* Attribute = static_cast<FWHAttribute*>(AttributePtr);

		Stack.Step(Stack.Object, NULL);
		FProperty* BoolResultProperty = CastField<FBoolProperty>(Stack.MostRecentProperty);
		void* BoolResultPtr = Stack.MostRecentPropertyAddress;
		bool* bResult = static_cast<bool*>(AttributePtr);
		// We need this to wrap up the stack
		P_FINISH;
		*bResult = SetAttribute_impl(InputProperty, InputPtr, *Attribute);
	}
	static bool SetAttribute_impl(FProperty* Property, void* StructPtr, FWHAttribute& Attribute);


	UFUNCTION(BlueprintPure)
	static void GetAllTypeName(TArray<FName>& OutArray)
	{
		const TMap<FName, FFieldClass*>& MapField= FFieldClass::GetNameToFieldClassMap();
		MapField.GetKeys(OutArray);
	}

	UFUNCTION(BlueprintPure)
	static void GetAllCppTypes(TArray<FString>& OutArray)
	{
		const auto& Fields= FFieldClass::GetAllFieldClasses();
		OutArray.Empty(Fields.Num());
		for (const auto &FieldClass : Fields)
		{
			FField* FieldCDO = FieldClass->Construct(UClass::StaticClass()->GetOutermost(), *FString::Printf(TEXT("Default__%s"), *FieldClass->GetName()), RF_Transient | RF_ClassDefaultObject);
			if (FieldCDO)
			{
				FProperty* Prop = CastField<FProperty>(FieldCDO);
				if (Prop)
				{
					OutArray.Add(Prop->GetCPPType());
				}
			}
		}
	}


	template<typename CppType>
	static bool bIsCppTypeProperty(FField* Field)
	{
		auto as_casted = dynamic_cast<TProperty<CppType, FProperty>>(Field);
		return as_casted != nullptr;
	}


	template<typename CppType>
	static TOptional<CppType> GetAttributeValue(const FWHAttribute& Attribute)
	{

	}


};
