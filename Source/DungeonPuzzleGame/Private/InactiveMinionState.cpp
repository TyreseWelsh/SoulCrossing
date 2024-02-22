// Fill out your copyright notice in the Description page of Project Settings.


#include "InactiveMinionState.h"
#include "../Minion.h"
#include "EnhancedInputSubsystems.h"
#include "MinionPlayerController.h"

// CANNOT DO ANY ACTIONS IN THE INACTIVE STATE, PURELY FOR THE VISUAL AND SEPARATION

void UInactiveMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);
}

void UInactiveMinionState::OnTickState()
{
	Super::OnTickState();
}

void UInactiveMinionState::OnExitState()
{
	Super::OnExitState();
}

void UInactiveMinionState::PressMove(const FInputActionValue& Value)
{
}

void UInactiveMinionState::Look(const FInputActionValue& Value)
{
	Super::Look(Value);																		// Can still look in inactive state. Inputs during inactive state are only relevant during the possession animation
}

void UInactiveMinionState::PressJump()
{
}

void UInactiveMinionState::PressUnPossess()
{
}

void UInactiveMinionState::PressInteract(const FInputActionValue& Value)
{
}
