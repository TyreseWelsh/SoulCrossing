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


bool UGameplayStateMachineComponent::SwitchState(FGameplayTag NewStateTag)
{
	return false;
}

// Called when the game starts
void UGameplayStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameplayStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGameplayStateMachineComponent::InitState()
{
	if (InitStateDelegate.IsBound())
	{
		InitStateDelegate.Broadcast(StateTag);
	}
}

void UGameplayStateMachineComponent::TickState(float DeltaTime)
{
	if (TickStateDelegate.IsBound())
	{
		TickStateDelegate.Broadcast(StateTag);
	}
}

void UGameplayStateMachineComponent::EndState()
{
	if (EndStateDelegate.IsBound())
	{
		EndStateDelegate.Broadcast(StateTag);
	}
}

