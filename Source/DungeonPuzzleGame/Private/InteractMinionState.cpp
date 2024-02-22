// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractMinionState.h"

void UInteractMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);
}

void UInteractMinionState::OnTickState()
{
	Super::OnTickState();
}

void UInteractMinionState::OnExitState()
{
	Super::OnExitState();
}

void UInteractMinionState::PressMove(const FInputActionValue& Value)
{
}

void UInteractMinionState::Look(const FInputActionValue& Value)
{
}

void UInteractMinionState::PressJump()
{
}

void UInteractMinionState::PressUnPossess()
{
}

void UInteractMinionState::PressInteract(const FInputActionValue& Value)
{
}
