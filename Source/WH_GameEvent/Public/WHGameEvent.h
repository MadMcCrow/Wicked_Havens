// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WHGameEvent.generated.h"


class AActor;
class UWHGameEvent;

DECLARE_LOG_CATEGORY_EXTERN(LogWHGameEvent, Log, All);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FWHOnGameEventEnd, UWHGameEvent, OnGameEventEnd, bool, bIsSuccess);


/**
 *	UWHGameEvent
 *	A game event is a scripting object that will execute a script on both server and client in an optimised way
 *	@note
 */
UCLASS(ClassGroup=(WH), Category="Petrichor|GameEvent", DefaultToInstanced, EditInlineNew)
class WH_GAMEEVENT_API UWHGameEvent : public UObject
{
	GENERATED_BODY()

public:

	// CTR
	UWHGameEvent( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	/**
	 *	Start event
	 *	It will try to start event on both server and client
	 */
	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void StartEvent(AActor * Source, AActor* Target);

	/**
	 *	OnEventStart
	 *	Specify that this event is done
	 */
	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void EndEvent(bool bEndSuccess = true);

	/**
	 *	CanRunEvent
	 *	Check if the event has the necessary requirements to run.
	 * 	@note Run on Authority only
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent")
	bool CanRunEvent() const;
	virtual bool CanRunEvent_Implementation() const;

	/**
	 *	OnServerEventStart
	 *	Server Only event.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent|Server")
	void OnServerEventStart();
	virtual void OnServerEventStart_Implementation();

	/**
	 *	OnClientEventStart
	 *	Clients event.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "GameEvent|Client")
	void OnClientEventStart();
	virtual void OnClientEventStart_Implementation();

	/**
	*	OnOwningClientEventStart
	*	Owning client only event.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "GameEvent|Client")
	void OnOwningClientEventStart();
	virtual void OnOwningClientEventStart_Implementation();


	/**
	 *	OnEventStart
	 *	Other Clients, Server and Owning client
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent|Multicast")
	void OnEventStart();
	virtual void OnEventStart_Implementation();

	/**
	*	OnEventStart
	*	Other Clients, Server and Owning client
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent|Multicast")
	void OnEventEnd();
	virtual void OnEventEnd_Implementation();

	/**
	 *	GetSource
	 *	return Source/Instigator for scripting
	 */
	UFUNCTION(BlueprintPure, Category = "GameEvent",  meta = (HideSelfPin = "true", CompactNodeTitle = "Source"))
	virtual AActor* GetSource() const;

	/**
	 *	GetTarget
	 *	return Target for scripting
	 */
	UFUNCTION(BlueprintPure, Category = "GameEvent",  meta = (HideSelfPin = "true",  CompactNodeTitle = "Target"))
	virtual AActor* GetTarget() const;

	/**
	 *	IsRunning
	 *	return bIsRunning for scripting
	 */
	UFUNCTION(BlueprintPure, Category = "GameEvent",  meta = (HideSelfPin = "true",  CompactNodeTitle = "Is Running ?"))
	virtual bool IsRunning() const;

	/**
	*	IsRunning
	*	return bIsRunning for scripting
	*/
	UFUNCTION(BlueprintPure, Category = "GameEvent",  meta = (HideSelfPin = "true",  CompactNodeTitle = "Is Success ?"))
	virtual bool IsSuccess() const;

	//------ Server Functions -----//
private:

	/**
	 *	Start event on server
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void Net_StartServerEvent(AActor * Source, AActor* Target);
	void Net_StartServerEvent_Implementation(AActor * Source, AActor* Target);
	bool Net_StartServerEvent_Validate(AActor * Source, AActor* Target) {return true;}

	/**
	 *	Start event on all clients
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_StartClientEvent(AActor * Source, AActor* Target);
	void Net_StartClientEvent_Implementation(AActor * Source, AActor* Target);
	bool Net_StartClientEvent_Validate(AActor * Source, AActor* Target) {return true;}

	/**
	 *	End event on all clients
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_EndClientEvent(bool bEndSuccess);
	void Net_EndClientEvent_Implementation(bool bEndSuccess);
	bool Net_EndClientEvent_Validate(bool bEndSuccess) {return true;}

public:

	UPROPERTY(BlueprintAssignable, Category="GameEvent|Events")
	FWHOnGameEventEnd OnGameEventEnd;

protected:
	/**
	 *	bReplicatedEvent
	 *	will this event be executed on remote machines
	 *	@note this is useful for local only events
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameEvent|Replication")
	bool bReplicatedEvent;

	/**
	 *	bClientRunEvent
	 *	Should client execute OnEventStart
	 *	@note this is useful if you want client only to simulate event, without doing anything
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameEvent|Replication")
	bool bClientRunEvent;

	/**
	 *	bClientRunEvent
	 *	Should server execute OnEventStart
	 *	@note this is useful if you want StartEvent to only happen on client
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameEvent|Replication")
	bool bServerRunEvent;

	/** Get local role (from source/instigator of event) */
	UFUNCTION(BlueprintPure, Category="GameEvent")
	ENetRole GetLocalRole() const;

	/** Get remote role (from source/instigator of event) */
	UFUNCTION(BlueprintPure, Category="GameEvent")
	ENetRole GetRemoteRole() const;


private:
	/** Source of this event and who will be responsible for handling it */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="GetSource")
	AActor * Instigator;

	/** Target for this Event, might be equal to Instigator */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="GetTarget")
	AActor * TargetActor;

	/** Target for this Event, might be equal to Instigator */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="IsRunning")
	bool bIsRunning;

	/** Target for this Event, might be equal to Instigator */
	UPROPERTY(Transient, DuplicateTransient, BlueprintGetter="IsSuccess")
	bool bIsSuccess;
};
