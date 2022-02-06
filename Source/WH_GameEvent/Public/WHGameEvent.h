/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "WHGameEvent.generated.h"


/**
 *	UWHGameEvent
 *	A game event is a scripting object that will execute a script on both server and client in an optimised way
 *	@note
 */
UCLASS(ClassGroup=(WH), Category="GameEvent")
class WH_GAMEEVENT_API AWHGameEvent : public AInfo
{
	GENERATED_BODY()

public:

	// CTR
	UWHGameEvent( const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	/**
	 *	LaunchEvent
	 *	Request the event to the server.
	 *	@param	Source	Actor making the request
	 *	@param  Target	Actor concerned by the result
	 *	@return false on failed validation
	 */
	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void LaunchEvent(AActor * Source, AActor* Target);

	/**
	 *	StopEvent
	 *	Terminate the event
	 *	@note events will stop existing if instigator or target stop existing 
	 */
	UFUNCTION(BlueprintCallable, Category = "GameEvent")
	void StopEvent(bool bEndSuccess = true);

	/**
	 *	CanRunEvent
	 *	Check if the event has the necessary requirements to run.
	 * 	@note Run on Authority only
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent")
	bool CanRunEvent() const;
	virtual bool CanRunEvent_Implementation() const;

	/**
	 *	CanStopEvent
	 *	Check if the event has the necessary requirements to run.
	 * 	@note Run on Authority only
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent")
	bool CanStopEvent() const;
	virtual bool CanStopEvent_Implementation() const;

	/**
	 *	BeginEvent
	 *	Plays when the event begins
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent", meta=(DisplayName="OnEventBegin"))
	void BeginEvent();
	virtual void BeginEvent_Implementation();

	/**
	 *	EndEvent
	 *	Plays when the event finishes
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "GameEvent" meta=(DisplayName="OnEventEnd"))
	void EndEvent(bool bEndSuccess);
	virtual void EndEvent_Implementation(bool bEndSuccess);


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


private:

	/**
	 *	Start event on server
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void Net_RequestEventStart(AActor * Source, AActor* Target);
	void Net_RequestEventStart_Implementation(AActor * Source, AActor* Target);
	bool Net_RequestEventStart_Validate(AActor * Source, AActor* Target) {return true;}

	UFUNCTION(Server, Reliable, WithValidation)
	void Net_RequestEventStop(bool bEndSuccess);
	void Net_RequestEventStop_Implementation(bool bEndSuccess);
	bool Net_RequestEventStop_Validate(bool bEndSuccess) {return true;}

	/**
	 *	Run Event on all client
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_PlayEvent();
	void Net_PlayEvent_Implementation();
	bool Net_PlayEvent_Validate() {return true;}

	/**
	 *	End event on all clients
	 */
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Net_EndEvent(bool bEndSuccess);
	void Net_EndEvent_Implementation(bool bEndSuccess);
	bool Net_EndEvent_Validate(bool bEndSuccess) {return true;}


private:

	/** Source of this event and who will be responsible for handling it */
	UPROPERTY(Replicated, BlueprintGetter="GetSource")
	AActor * Instigator;

	/** Target for this Event, might be equal to Instigator */
	UPROPERTY(Replicated, BlueprintGetter="GetTarget")
	AActor * TargetActor;

};
