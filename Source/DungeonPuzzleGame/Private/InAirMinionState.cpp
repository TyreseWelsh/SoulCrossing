// Fill out your copyright notice in the Description page of Project Settings.


#include "InAirMinionState.h"
#include "../Minion.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayStateManagerComponent.h"

void UInAirMinionState::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);
}

void UInAirMinionState::OnTickState()
{
	Super::OnTickState();

	if (PlayerReference != nullptr)
	{
		if (PlayerReference->GetCharacterMovement()->Velocity.Z == 0)
		{
			PlayerReference->StateManagerComponent->SwitchStateByKey("Idle");
		}
	}
}

void UInAirMinionState::OnExitState()
{
	Super::OnExitState();
}

void UInAirMinionState::PressMove(const FInputActionValue& Value)
{
	Super::PressMove(Value);
}

void UInAirMinionState::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void UInAirMinionState::PressJump()
{
	// CANT JUMP IN AIR STATE
}

void UInAirMinionState::PressUnPossess()
{
	// CANT UNPOSSESS IN AIR STATE
}

void UInAirMinionState::PressInteract(const FInputActionValue& Value)
{
	// CANT INTERACT IN AIR STATE (MIGHT SWAP ROGUE SKELETON CLIMB TO INTERACT FROM ABILITY(?))
}
