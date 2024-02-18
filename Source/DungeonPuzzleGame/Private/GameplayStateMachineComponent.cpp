// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayStateMachineComponent.h"

// Sets default values for this component's properties
UGameplayStateMachineComponent::UGameplayStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGameplayStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialising the starting state by switching to it (calling the InitState() function and other variables)
	SwitchState(InitialStateTag);
}


// Called every frame
void UGameplayStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bStateCanTick)
	{
		TickState(DeltaTime);
	}

	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("Current State of %s: %s"), *GetOwner()->GetName(), *CurrentStateTag.ToString()));

		// Maybe here add screen debug message to show state history if cba
	}
}

bool UGameplayStateMachineComponent::SwitchState(FGameplayTag NewStateTag)
{
	// Checking if the new state we want to switch to is the same as the current state we are in or not
	if (!NewStateTag.MatchesTagExact(CurrentStateTag))
	{
		// Ending current state
		bStateCanTick = false;
		EndState();
		
		// Reassigning current state as new state we are switching to and initialising it
		CurrentStateTag = NewStateTag;
		InitState();
		bStateCanTick = true;

		if (StateChangedDelegate.IsBound())
		{
			StateChangedDelegate.Broadcast(CurrentStateTag);
		}

		return true;
	}
	else
	{
		// Prints warning to output log if current state is the same as the new state.
		// First string parameter is the name of the owning actor object and the second string parameter is the name of the new state (which should be the same as the current state)
		if (bDebug)
		{
			UE_LOG(LogTemp, Warning, TEXT("WARNING: Couldnt switch state for %s because it is already in state %s"), *GetOwner()->GetName(), *NewStateTag.ToString());
		}
	}

	return false;
}

void UGameplayStateMachineComponent::InitState()
{
	if (InitStateDelegate.IsBound())
	{
		InitStateDelegate.Broadcast(CurrentStateTag);
	}
}

void UGameplayStateMachineComponent::TickState(float DeltaTime)
{
	if (TickStateDelegate.IsBound())
	{
		TickStateDelegate.Broadcast(DeltaTime, CurrentStateTag);
	}
}

void UGameplayStateMachineComponent::EndState()
{
	if (StateHistory.Num() >= MaxStateHistoryLength)
	{
		StateHistory.RemoveAt(0);
	}

	StateHistory.Add(CurrentStateTag);

	if (EndStateDelegate.IsBound())
	{
		EndStateDelegate.Broadcast(CurrentStateTag);
	}
}