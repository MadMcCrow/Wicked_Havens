// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "GameEvent/WHCompositeGameEvent.h"

UWHCompositeGameEvent::UWHCompositeGameEvent( const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UWHCompositeGameEvent::IsRunning() const
{
	for (auto GE : GameEvents)
	{
		if (GE->IsRunning())
		{
			return true;
		}
	}
	return Super::IsRunning();
}

void UWHCompositeGameEvent::OnEventStart_Implementation()
{
	Super::OnEventStart_Implementation();
	switch(PlayMode)
	{
	default:
	case EWHCompositeGameEventPlayMode::Synchronous:
		PlaySynchronous();
		break;
	case EWHCompositeGameEventPlayMode::Sequence:
	case EWHCompositeGameEventPlayMode::SequenceWithFailStop:
		SequenceIdx = 0;
		PlaySequence();
		break;
	}
}

void UWHCompositeGameEvent::OnEventEnd_Implementation()
{
	Super::OnEventEnd_Implementation();
	switch(PlayMode)
	{
	default:
	case EWHCompositeGameEventPlayMode::Synchronous:
		return;
	case EWHCompositeGameEventPlayMode::SequenceWithFailStop:
		if(!IsSuccess())
		{
			SequenceIdx = 0;
			return;
		}
		// FALLTHROUGH !
	case EWHCompositeGameEventPlayMode::Sequence:
		PlaySequence();
		break;
	}

}

void UWHCompositeGameEvent::PlaySynchronous()
{
	for (auto GE : GameEvents)
	{
		if (GE != nullptr)
		{
			GE->StartEvent(GetSource(), GetTarget());
		}
	}
}

void UWHCompositeGameEvent::PlaySequence()
{
	if (GameEvents.IsValidIndex(SequenceIdx))
	{
		GameEvents[SequenceIdx]->OnGameEventEnd.AddUniqueDynamic(this, &UWHCompositeGameEvent::EndEvent);
		GameEvents[SequenceIdx]->StartEvent(GetSource(), GetTarget());
		SequenceIdx++; // NEXT !
	}
	else
	{
		// Reached the end !
		EndEvent(true);
	}
}
