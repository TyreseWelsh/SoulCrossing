// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayStateManagerComponent.h"

// Sets default values for this component's properties
UGameplayStateManagerComponent::UGameplayStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameplayStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitStates();
}


// Called every frame
void UGameplayStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bCanTickState)
	{
		CurrentState->OnTickState();
	}

	if (CurrentState->IsValidLowLevel() && bDebug)
	{
		UE_LOG(LogTemp, Error, TEXT("Current State: %s"), *CurrentState->GetName());
	}
}

void UGameplayStateManagerComponent::SwitchStateByKey(FString NewStateKey)
{
	UStateBase* NewState = StateMap.FindRef(NewStateKey);												// Finding new state using state key given, (used to compare with curren state)

	if (NewState->IsValidLowLevel())																	// Checks if object is valid
	{
		if (!CurrentState)																				// If there is no CurrentState (is null), it means we have just started the game, initialising first state
		{
			CurrentState = NewState;
		}
		else
		{
			if (CurrentState->GetClass() == NewState->GetClass() && !CurrentState->bCanLoop)
			{
				if (bDebug)
				{
					UE_LOG(LogTemp, Error, TEXT("ERROR: %s State Cannot Loop!"), *CurrentState->GetName());
				}
			}
			else
			{
				bCanTickState = false;
				CurrentState->OnExitState();

				if (StateHistory.Num() >= MaxStateHistoryLength)										// If state history is full, remove the first element (oldest state) and then push the current state on the end
				{
					StateHistory.RemoveAt(0);
				}
				StateHistory.Push(CurrentState);

				CurrentState = NewState;
			}
		}

		CurrentState->OnEnterState(GetOwner());
		bCanTickState = true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: % s State Is Not Valid!"), *CurrentState->GetName());
	}
}

void UGameplayStateManagerComponent::SwitchState(UStateBase* NewState)
{
}

void UGameplayStateManagerComponent::InitStateManager()
{
	SwitchStateByKey(InitialState);
}

void UGameplayStateManagerComponent::InitStates()
{
	// Iterating over all of the pairs in the available states map, constructing a new StateBase obj using the available states value (which is a child of UStateBase), then adding this new State to the StateMap variable
	for (auto It = AvailableStates.CreateConstIterator(); It; ++It)
	{
		UStateBase* State = NewObject<UStateBase>(this, It->Value);
		StateMap.Add(It->Key, State);
	}
}
