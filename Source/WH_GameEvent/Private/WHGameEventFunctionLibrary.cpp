/* Copyright © Noé Perard-Gayot 2022. */

#include "WHGameEventFunctionLibrary.h"
#include "WHGameEvent.h"
#include "WHGameEventSubsystem.h"

void UWHGameEventFunctionLibrary::LaunchGameEvent(const UObject* WorldContextObject, FSoftClassPath EventClass, AActor * Source, AActor* Target)
{
	if (!WorldContextObject)
		return;

	if (const auto GESS = WorldContextObject->GetWorld()->GetSubsystem<UWHGameEventSubsystem>())
	{
		if (UClass* Class = EventClass.TryLoadClass<UWHGameEvent>())
		{
			const auto GE =NewObject<UWHGameEvent>(GESS);
			if (GE->CanRunEvent(Source, Target))
			{
				GESS->RegisterGameEvent(GE);
			}
		}
	}
}