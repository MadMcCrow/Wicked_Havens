/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeSubsystem.h"
#include "WHAttributeSettings.h"
#include "WHAttributeType.h"

const FName ErrorName = FName();
const FWHAttributeType ErrorType = FWHAttributeType();

UWHAttributeSubsystem::UWHAttributeSubsystem() : Super()
{
}

void UWHAttributeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// make sure arrays are empty
	FieldClassDefaultObjects.Empty();
	GameAttributeNames.Empty();
	GameAttributeTypes.Empty();
	// init types from Engine
	InitializeAllTypes();
	// import settings
	ImportSettings();
}

void UWHAttributeSubsystem::Deinitialize()
{
	// Empty our arrays
	GameAttributeNames.Empty();
	GameAttributeTypes.Empty();
	FieldClassDefaultObjects.Empty();
	Super::Deinitialize();
}

bool UWHAttributeSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

const FWHAttributeType& UWHAttributeSubsystem::GetAttributeType(const FWHAttributeName& InName)
{
	return ErrorType;
}

const FName& UWHAttributeSubsystem::GetAttributeFName(const FWHAttributeName& InName)
{
	if (const auto NamePtr = GameAttributeNames.Find(InName.GetID()))
	{
		return *NamePtr;
	}
	return ErrorName;
}

FWHAttributeName UWHAttributeSubsystem::FindAttributeName(const FName& InFName)
{
	if (const FGuid* GuidPtr = GameAttributeNames.FindKey(InFName))
	{
		return FWHAttributeName(*GuidPtr);
	}
	return FWHAttributeName();
}

void UWHAttributeSubsystem::ImportSettings()
{
	// delete previously stored data
	GameAttributeTypes.Reset();
	GameAttributeNames.Reset();
	if (const UWHAttributeSettings* const Settings = GetDefault<UWHAttributeSettings>())
	{
		const auto& Definitions = Settings->GetAttributeDefinitions();
		const auto SlackSize =Definitions.Num();
		GameAttributeTypes.Reserve(SlackSize);
		GameAttributeNames.Reserve(SlackSize);
		for (const auto& Definition : Definitions)
		{
			//GameAttributeTypes.Add(Definition.GetAttributeTypeDefinition());
			GameAttributeNames.Add(Definition.GetAttributeNameDefinition());
		}
	}

	// Make sure to have some slack;
	GameAttributeTypes.Shrink();
	GameAttributeNames.Shrink();
}

#if WITH_EDITOR
void UWHAttributeSubsystem::GetAllNames(TArray<FName>& OutNames)
{
	if (const auto WHASS = Get())
		WHASS->GameAttributeNames.GenerateValueArray(OutNames);
}
#endif //WITH_EDITOR


void UWHAttributeSubsystem::InitializeAllTypes()
{
	FieldClassDefaultObjects.Empty();
	const auto& Fields= FFieldClass::GetAllFieldClasses();
	FieldClassDefaultObjects.Reserve(Fields.Num());
	for (const auto &FieldClass : Fields)
	{
		if (FField* FieldCDO = FieldClass->Construct(this, *FString::Printf(TEXT("WHAttributeType_%s"), *FieldClass->GetName()), RF_Transient | RF_ClassDefaultObject))
		{
			FString CppType = TEXT("Undefined");
			TObjectPtr<UStruct> DataType;
			if (CastField<FBoolProperty>(FieldCDO))
			{
				CppType = TEXT("bool");
			}
			else if (CastField<FFloatProperty>(FieldCDO))
			{
				CppType = TEXT("float");
			}
			else if (CastField<FDoubleProperty>(FieldCDO))
			{
				CppType = TEXT("double");
			}
			else if (CastField<FIntProperty>(FieldCDO))
			{
				CppType = TEXT("int32");
			}
			else if (CastField<FNameProperty>(FieldCDO))
			{
				CppType = TEXT("FName");
			}
			else if (CastField<FStrProperty>(FieldCDO))
			{
				CppType = TEXT("FString");
			}
			else if (FStructProperty* StructProperty = CastField<FStructProperty>(FieldCDO))
			{
				CppType = TEXT("Struct");
				if (StructProperty->Struct)
				{
					DataType = StructProperty->Struct;
				}
			}
			else
			{
				CppType = FieldCDO->GetName();
			}
			FieldClassDefaultObjects.Add(CppType, FieldCDO);
		}
	}
	FieldClassDefaultObjects.Shrink();
}
