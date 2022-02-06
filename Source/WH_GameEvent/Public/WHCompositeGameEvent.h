// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "WHGameEvent.h"
#include "WHCompositeGameEvent.generated.h"

/**
 *	EWHCompositeGameEventPlayMode
 *	Defines how a composite GameEvent plays it's events
 *	@note	We could add Select, Random, etc
 *	@todo	Determine the usefullness of other types
 */
UENUM(BlueprintType, Category="Petrichor|GameEvent")
enum class EWHCompositeGameEventPlayMode : uint8
{
	Synchronous			 = 0 UMETA(DisplayName="Synchronous",		 Tooltip="Play all events at once"),
	Sequence			 = 1 UMETA(DisplayName="Sequence",			 Tooltip="Play all events in a sequence"),
	SequenceWithFailStop = 2 UMETA(DisplayName="Sequence With Stop", Tooltip="Play all events in a sequence, stop if one fails"),
};

/**
 *	UWHCompositeGameEvent
 *	A game event that will start a list of GameEvents.
 *	They can be all started at once or back to back.
 *	@todo : This might benefit from a custom editor for GameEvents
 */
UCLASS(ClassGroup=(WH), Category="Petrichor|GameEvent", DefaultToInstanced, EditInlineNew)
class WH_GAMEEVENT_API UWHCompositeGameEvent : public UWHGameEvent
{
	GENERATED_BODY()

public:

	// CTR
	UWHCompositeGameEvent( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	// UWHGameEvent API
	virtual bool IsRunning() const override;
	virtual void OnEventStart_Implementation() override;
	virtual void OnEventEnd_Implementation() override;
	// \UWHGameEvent API

protected:
	/**
	 *	GameEvents
	 *	the list of game events to play
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="GameEvent|Composite")
	TArray<UWHGameEvent*> GameEvents;

	/**
	 *	GameEvents
	 *	the list of game events to play
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameEvent|Composite")
	EWHCompositeGameEventPlayMode PlayMode;

private:
	/** Call all events at once */
	void PlaySynchronous();

	/** Call all events, waiting for each to end to start the next */
	void PlaySequence();

	UPROPERTY(Transient, DuplicateTransient)
	int32 SequenceIdx;

};
