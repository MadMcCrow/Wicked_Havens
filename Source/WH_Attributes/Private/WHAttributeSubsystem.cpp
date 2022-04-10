/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeSubsystem.h"
#include "WHAttribute.h"
#if WITH_EDITOR
#include "UObject/ObjectSaveContext.h"
#endif // WITH_EDITOR

void UWHAttributeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
#if WITH_EDITOR
	OnPreSaveDelegate = FCoreUObjectDelegates::OnObjectPreSave.AddUObject(this,&UWHAttributeSubsystem::OnObjectPreSave);
#endif // WITH_EDITOR
	RefreshAttributes();
}

void UWHAttributeSubsystem::Deinitialize()
{
	AttributeObjects.Empty();
#if WITH_EDITOR
	FCoreUObjectDelegates::OnObjectPreSave.Remove(OnPreSaveDelegate);
#endif // WITH_EDITOR
	Super::Deinitialize();
}

UWHAttributeBase* UWHAttributeSubsystem::GetAttributeObject(const FWHAttributeRef& Ref)
{
	const auto AttributeSubsystem = GEngine->GetEngineSubsystem<UWHAttributeSubsystem>();
	if(UNLIKELY(ensureMsgf(!AttributeSubsystem, TEXT("Attribute Subsystem not found"))))
		return nullptr;
		
	if (const auto FoundObject = AttributeSubsystem->AttributeObjects.Find(Ref))
		return DuplicateObject<UWHAttributeBase>(*FoundObject, AttributeSubsystem); 	// TODO: use pool instead

#if WITH_EDITOR
	if (Ref.IsValid())
		ensureAlwaysMsgf(false, TEXT("Attribute with non-registered attribute class detected"));
#endif // WITH_EDITOR
	return nullptr;
}


void UWHAttributeSubsystem::RefreshAttributes()
{
	AttributeObjects.Reserve(300);
	for (TObjectIterator<UClass> It; It; ++It)
	{
		const UClass* AttributeClass = *It;
		ensureAlways(AttributeClass != nullptr);
		if (AttributeClass->IsChildOf(UWHAttributeBase::StaticClass()) && AttributeClass->HasAnyClassFlags(CLASS_Abstract) == false)
		{
			FWHAttributeRef NewRef(AttributeClass);
			if (!AttributeObjects.Contains(NewRef))
			{
				constexpr auto Flags = RF_Public | RF_Transient;
				const FName NewAttributeName = MakeUniqueObjectName(this, AttributeClass, NAME_None);
				if (auto NewAttributeObject = NewObject<UWHAttributeBase>(this, AttributeClass, NewAttributeName, Flags))
					AttributeObjects.Add(NewRef,NewAttributeObject);
			}
		}
	}
	AttributeObjects.Shrink();
}

#if WITH_EDITOR
void UWHAttributeSubsystem::OnObjectPreSave(UObject* SavedObject, FObjectPreSaveContext Context)
{
	//RefreshAttributes();
	if (Context.IsCooking())
		return;

	if (Context.IsProceduralSave())
		return;

	if (SavedObject)
		UE_LOG(LogTemp, Error, TEXT("Save Object class is : %s"), *SavedObject->GetClass()->GetName());
}
#endif // WITH_EDITOR
