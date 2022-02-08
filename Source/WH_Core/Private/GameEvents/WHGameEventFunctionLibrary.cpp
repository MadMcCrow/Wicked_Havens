/* Copyright © Noé Perard-Gayot 2022. */

#include "GameEvents/WHGameEventFunctionLibrary.h"

#include "GameEvents/WHGameEvent.h"
#include "GameEvents/WHGameEventSubsystem.h"

void UWHGameEventFunctionLibrary::LaunchGameEvent(const UObject* WorldContextObject, FSoftClassPath EventClass, AActor * Source, AActor* Target)
{
	if (!WorldContextObject)
		return;

	if (auto GESS = WorldContextObject->GetWorld()->GetSubsystem<UWHGameEventSubsystem>())
	{
		if (UClass* Class = EventClass.TryLoadClass<UWHGameEvent>())
		{
			auto GE =NewObject<UWHGameEvent>(GESS);
			if (GE->CanRunEvent(Source, Target))
			{
				GESS->RegisterGameEvent(GE);
			}
		}
	}
}
